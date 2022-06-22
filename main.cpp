/*
    ------------------------------------------------------------------------------------------------------

    rb_copycolor command line utility

    Copies my "energy" rating for tracks from the rekordbox database prepared for CDJs to the 
    DENON Engine Prime database for Prime devices (such as my Prime Go).

    I use E1...E5 as rating (E5 being the party banger) and this translates into star ratings on the
    Prime device to 1-star for E1 til 5-star for E5.

    Usage: rb_copycolor <path_to_usb_device>

    Workflow

    - Prepare your usb device for CDJs using rekordbox
    - Plug it into the Prime device and load the rekordbox database (you'll need v2 of the firmware)
    - Unplug the device from the player and add it to your mac or pc
    - use rb_colorcopy to transfer the energy level information

    The import on the Prime device is pretty good, it catches cue points, loops, bpm and all sorts of
    metadata. So there is no need to use Engine DJ on the mac/PC to transfer the library. Of course
    the player will analyze on the fly, but this is pretty fast and - since the Prime Go is my secondary 
    set for smaller gigs - acceptable.

    Building

    - Just use cmake . and then make. I developed it on macos - so no guarantee for other platforms.
    - If you want to re-create the kaitai source files, you will need kaitai-struct-compiler. I recommend
      "brew install kaitai-struct-compiler" to get it. There is a shell script for convenience.

    For simplicity I copied the kaitai C++ interfaces lib files into this project instead of git-ting them in.

    Acknowledgements

    The information about rekordbox databases is mainly gathered from https://github.com/Deep-Symmetry/crate-digger
    who did an amazing job. They also pointed me to kaitai.io which is amazing for reading the pdb files.


    ------------------------------------------------------------------------------------------------------
    Copyright (c) 2022 Tim Hagemann / way2.net Services

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    ------------------------------------------------------------------------------------------------------
*/
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <unistd.h>

#include "rekordbox_pdb.h"

#include "sqlite3.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MyColor
{
public:
    uint32_t        m_id;
    std::string     m_name;
};

typedef std::map<uint32_t, MyColor> ColorMap;

ColorMap g_ColorMap;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MyTrack
{
public:
    uint32_t        m_id;
    std::string     m_filename;
    uint32_t        m_color_id;
};

typedef std::map<uint32_t, MyTrack> TrackMap;

TrackMap g_TrackMap;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef std::map<uint32_t, uint32_t> ColorIdStarsMap;

ColorIdStarsMap g_ColorIdStarsMap;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// --- function pointer typedef for handler functions

typedef void (*RowHandler)(rekordbox_pdb_t::row_ref_t *f_rr);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ColorHandler(rekordbox_pdb_t::row_ref_t *f_rr)
{
    // --- if present...we know that this is a track row...so cast it...

    rekordbox_pdb_t::color_row_t *l_cr = (rekordbox_pdb_t::color_row_t *)f_rr->body();

    // --- we also know that the filename is long ascii coded...so cast it

    rekordbox_pdb_t::device_sql_short_ascii_t *l_la = (rekordbox_pdb_t::device_sql_short_ascii_t *)l_cr->name()->body();

    // --- now add a new object to our map

    MyColor l_mc;

    l_mc.m_id   = l_cr->id();
    l_mc.m_name = l_la->text();
    
    g_ColorMap[l_mc.m_id] = l_mc;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TrackHandler(rekordbox_pdb_t::row_ref_t *f_rr)
{
    // --- if present...we know that this is a track row...so cast it...

    rekordbox_pdb_t::track_row_t *l_tr = (rekordbox_pdb_t::track_row_t *)f_rr->body();

    // --- we also know that the filename is long ascii coded...so cast it

    rekordbox_pdb_t::device_sql_long_ascii_t *l_la = (rekordbox_pdb_t::device_sql_long_ascii_t *)l_tr->file_path()->body();

    // --- now add a new object to our map

    MyTrack l_mt;

    l_mt.m_id   = l_tr->id();
    l_mt.m_color_id = l_tr->color_id();
    l_mt.m_filename = l_la->text();
    
    g_TrackMap[l_mt.m_id] = l_mt;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ScanTable(rekordbox_pdb_t::table_t *t,RowHandler f_handler)
{
    // --- remember the last page

    uint32_t l_lastpage = t->last_page()->index();
    
    // --- now loop all pages in the table

    rekordbox_pdb_t::page_ref_t *l_pageref = t->first_page();

    while (true)
    {
        // --- de-reference page ref to page

        rekordbox_pdb_t::page_t *l_page = l_pageref->body();

        // --- process page

        if (l_page->is_data_page())
        {
            // --- now iterate over all row groups

            for (std::vector<rekordbox_pdb_t::row_group_t*>::iterator l_rgit = l_page->row_groups()->begin(); l_rgit != l_page->row_groups()->end();++l_rgit)
            {
                // --- and now over all rows (using row refs)

                rekordbox_pdb_t::row_group_t *l_rg = *l_rgit;

                for (std::vector<rekordbox_pdb_t::row_ref_t*>::iterator l_rrit = l_rg->rows()->begin(); l_rrit != l_rg->rows()->end();++l_rrit)
                {
                    rekordbox_pdb_t::row_ref_t *l_rr = *l_rrit;

                    if (l_rr->present())
                    {
                        // --- call the handler

                        f_handler(l_rr);
                    }

                }
            }
        }

        // --- was this the last page? If so, exit

        if (l_page->page_index() == l_lastpage) break;

        // --- no: get next page's reference

        l_pageref = l_page->next_page();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
int sql_callback(void *f_param,int f_numcols,char **f_colvalue,char **f_colnames)
{
    for (int i=0; i < f_numcols; ++i)
    {
        printf("%s  --> %s \n",f_colnames[i],f_colvalue[i]);
    }

    return 0;
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    std::cout << "rb_copycolor v1.0 - rekordbox color to DENON DJ star converter" << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl << std::endl;

    if (argc != 2)
    {
        std::cout << "Usage: rb_copycolor <path_to_export_media>" << std::endl << std::endl;
        return 255;
    }

    // --- calculate filename to rekordbox database

    std::string l_filename = std::string(argv[1]) + "/PIONEER/rekordbox/export.pdb";
    std::string l_filename_denon = std::string(argv[1]) + "/Engine Library/Database2/m.db";

    // --- open Denon DJ SQLite db
    
    std::cout << "Opening Denon database file '" << l_filename_denon << "'" << std::endl;

    sqlite3 *l_sql_db;

    int l_rc = sqlite3_open_v2(l_filename_denon.c_str(), &l_sql_db,SQLITE_OPEN_READWRITE,NULL);
    if (l_rc)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(l_sql_db) << std::endl;
        sqlite3_close(l_sql_db);

        return 255;
    }

    // --- open the rekordbox database file

    std::cout << "Processing rekordbox export file '" << l_filename<< "'" << std::endl;

    try
    {
        std::ifstream ifs(l_filename, std::ifstream::binary);
        kaitai::kstream ks(&ifs);
        rekordbox_pdb_t g = rekordbox_pdb_t(&ks);

        // --- parse all tables

        for (std::vector<rekordbox_pdb_t::table_t*>::iterator it = g.tables()->begin(); it != g.tables()->end(); ++it)
        {
            rekordbox_pdb_t::table_t *t = *it;

            //std::cout << "Processing table " << t->type() << std::endl; 

            // --- if we found the right table

            switch (t->type())
            {
                case rekordbox_pdb_t::PAGE_TYPE_TRACKS:
                                                            ScanTable(t,TrackHandler);  
                                                            break;

                case rekordbox_pdb_t::PAGE_TYPE_COLORS:
                                                            ScanTable(t,ColorHandler);  
                                                            break;

                default:
                                                            break;

            } 

        }

        std::cout << "Database successfully parsed." << std::endl;

        // ---  now the real processing starts: first build a translate map between E1...5 and the color database id

        std::cout << std::endl << "Found " << g_ColorMap.size() << " color definitions in rekordbox export database:" << std::endl << std::endl;
        
        for (ColorMap::iterator it = g_ColorMap.begin();it != g_ColorMap.end();++it)
        {
            std::cout << it->second.m_id << " --> " << it->second.m_name << " : ";

            if (it->second.m_name.substr(0,1) != "E")                
            {
                std::cout << "ignored" << std::endl;
            }
            else
            {
                int l_starcnt = atoi(it->second.m_name.substr(1).c_str());
                std::cout << l_starcnt << " stars" << std::endl;

                // --- this is our translation map

                g_ColorIdStarsMap[it->second.m_id] = l_starcnt;
            }
        }

        // --- now parse through all tracks

        std::cout << std::endl << "Found " << g_TrackMap.size() << " tracks in rekordbox export database." << std::endl;

        int l_cnt = 0;
        int l_colorcnt = 0;

        for (TrackMap::iterator it = g_TrackMap.begin();it != g_TrackMap.end();++it)
        {   
            // --- some progress indicator

            if ((++l_cnt % 50) == 0)
            {
                std::cout << "Processed " << l_cnt << " tracks\r";
                std::cout.flush();
            }

            // --- if our tracks has a color id assigned

            if (it->second.m_color_id != 0)
            {
                l_colorcnt++;

                // --- translate color idx to rating

                int l_translated_rating = g_ColorIdStarsMap[it->second.m_color_id] * 20;

                // --- create update sql statement

                std::string l_sqlstm = "update Track set rating = '" + std::to_string(l_translated_rating) + "' where path=\".." + it->second.m_filename + "\";";

                //std::cout << l_sqlstm << std::endl;

                // --- process the statement

                char *l_errmsg;
                int l_rc = sqlite3_exec(l_sql_db,l_sqlstm.c_str(),NULL,NULL,&l_errmsg);
                if (l_rc)
                {
                    std::cerr << "Error updating Denon database " << l_errmsg << "\n";
                    return 255;
                }
            }
        }

        std::cout << "Processed " << l_cnt << " tracks of which " << l_colorcnt << " have a color rating\n";

        // --- cleanup

        sqlite3_close(l_sql_db);

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 255;
    }
    
    

    return 0;
}


