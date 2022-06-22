// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "rekordbox_pdb.h"
#include "kaitai/exceptions.h"

rekordbox_pdb_t::rekordbox_pdb_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_tables = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::_read() {
    m__unnamed0 = m__io->read_u4le();
    m_len_page = m__io->read_u4le();
    m_num_tables = m__io->read_u4le();
    m_next_unused_page = m__io->read_u4le();
    m__unnamed4 = m__io->read_u4le();
    m_sequence = m__io->read_u4le();
    m_gap = m__io->read_bytes(4);
    if (!(gap() == std::string("\x00\x00\x00\x00", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x00\x00\x00\x00", 4), gap(), _io(), std::string("/seq/6"));
    }
    int l_tables = num_tables();
    m_tables = new std::vector<table_t*>();
    m_tables->reserve(l_tables);
    for (int i = 0; i < l_tables; i++) {
        m_tables->push_back(new table_t(m__io, this, m__root));
    }
}

rekordbox_pdb_t::~rekordbox_pdb_t() {
    _clean_up();
}

void rekordbox_pdb_t::_clean_up() {
    if (m_tables) {
        for (std::vector<table_t*>::iterator it = m_tables->begin(); it != m_tables->end(); ++it) {
            delete *it;
        }
        delete m_tables; m_tables = 0;
    }
}

rekordbox_pdb_t::device_sql_string_t::device_sql_string_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::device_sql_string_t::_read() {
    m_length_and_kind = m__io->read_u1();
    switch (length_and_kind()) {
    case 64: {
        m_body = new device_sql_long_ascii_t(m__io, this, m__root);
        break;
    }
    case 144: {
        m_body = new device_sql_long_utf16le_t(m__io, this, m__root);
        break;
    }
    default: {
        m_body = new device_sql_short_ascii_t(length_and_kind(), m__io, this, m__root);
        break;
    }
    }
}

rekordbox_pdb_t::device_sql_string_t::~device_sql_string_t() {
    _clean_up();
}

void rekordbox_pdb_t::device_sql_string_t::_clean_up() {
    if (m_body) {
        delete m_body; m_body = 0;
    }
}

rekordbox_pdb_t::history_playlist_row_t::history_playlist_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::history_playlist_row_t::_read() {
    m_id = m__io->read_u4le();
    m_name = new device_sql_string_t(m__io, this, m__root);
}

rekordbox_pdb_t::history_playlist_row_t::~history_playlist_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::history_playlist_row_t::_clean_up() {
    if (m_name) {
        delete m_name; m_name = 0;
    }
}

rekordbox_pdb_t::playlist_tree_row_t::playlist_tree_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;
    f_is_folder = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::playlist_tree_row_t::_read() {
    m_parent_id = m__io->read_u4le();
    m__unnamed1 = m__io->read_bytes(4);
    m_sort_order = m__io->read_u4le();
    m_id = m__io->read_u4le();
    m_raw_is_folder = m__io->read_u4le();
    m_name = new device_sql_string_t(m__io, this, m__root);
}

rekordbox_pdb_t::playlist_tree_row_t::~playlist_tree_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::playlist_tree_row_t::_clean_up() {
    if (m_name) {
        delete m_name; m_name = 0;
    }
}

bool rekordbox_pdb_t::playlist_tree_row_t::is_folder() {
    if (f_is_folder)
        return m_is_folder;
    m_is_folder = raw_is_folder() != 0;
    f_is_folder = true;
    return m_is_folder;
}

rekordbox_pdb_t::color_row_t::color_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::color_row_t::_read() {
    m__unnamed0 = m__io->read_bytes(5);
    m_id = m__io->read_u2le();
    m__unnamed2 = m__io->read_u1();
    m_name = new device_sql_string_t(m__io, this, m__root);
}

rekordbox_pdb_t::color_row_t::~color_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::color_row_t::_clean_up() {
    if (m_name) {
        delete m_name; m_name = 0;
    }
}

rekordbox_pdb_t::device_sql_short_ascii_t::device_sql_short_ascii_t(uint8_t p_length_and_kind, kaitai::kstream* p__io, rekordbox_pdb_t::device_sql_string_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_length_and_kind = p_length_and_kind;
    f_length = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::device_sql_short_ascii_t::_read() {
    m_text = kaitai::kstream::bytes_to_str(m__io->read_bytes((length() - 1)), std::string("ascii"));
}

rekordbox_pdb_t::device_sql_short_ascii_t::~device_sql_short_ascii_t() {
    _clean_up();
}

void rekordbox_pdb_t::device_sql_short_ascii_t::_clean_up() {
}

int32_t rekordbox_pdb_t::device_sql_short_ascii_t::length() {
    if (f_length)
        return m_length;
    m_length = (length_and_kind() >> 1);
    f_length = true;
    return m_length;
}

rekordbox_pdb_t::album_row_t::album_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;
    f_name = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::album_row_t::_read() {
    m__unnamed0 = m__io->read_u2le();
    m_index_shift = m__io->read_u2le();
    m__unnamed2 = m__io->read_u4le();
    m_artist_id = m__io->read_u4le();
    m_id = m__io->read_u4le();
    m__unnamed5 = m__io->read_u4le();
    m__unnamed6 = m__io->read_u1();
    m_ofs_name = m__io->read_u1();
}

rekordbox_pdb_t::album_row_t::~album_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::album_row_t::_clean_up() {
    if (f_name) {
        if (m_name) {
            delete m_name; m_name = 0;
        }
    }
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::album_row_t::name() {
    if (f_name)
        return m_name;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_name()));
    m_name = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_name = true;
    return m_name;
}

rekordbox_pdb_t::page_t::page_t(kaitai::kstream* p__io, rekordbox_pdb_t::page_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_next_page = 0;
    m_row_groups = 0;
    f_num_rows = false;
    f_num_groups = false;
    f_row_groups = false;
    f_heap_pos = false;
    f_is_data_page = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::page_t::_read() {
    m_gap = m__io->read_bytes(4);
    if (!(gap() == std::string("\x00\x00\x00\x00", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x00\x00\x00\x00", 4), gap(), _io(), std::string("/types/page/seq/0"));
    }
    m_page_index = m__io->read_u4le();
    m_type = static_cast<rekordbox_pdb_t::page_type_t>(m__io->read_u4le());
    m_next_page = new page_ref_t(m__io, this, m__root);
    m__unnamed4 = m__io->read_u4le();
    m__unnamed5 = m__io->read_bytes(4);
    m_num_rows_small = m__io->read_u1();
    m__unnamed7 = m__io->read_u1();
    m__unnamed8 = m__io->read_u1();
    m_page_flags = m__io->read_u1();
    m_free_size = m__io->read_u2le();
    m_used_size = m__io->read_u2le();
    m__unnamed12 = m__io->read_u2le();
    m_num_rows_large = m__io->read_u2le();
    m__unnamed14 = m__io->read_u2le();
    m__unnamed15 = m__io->read_u2le();
    n_heap = true;
    if (false) {
        n_heap = false;
        m_heap = m__io->read_bytes_full();
    }
}

rekordbox_pdb_t::page_t::~page_t() {
    _clean_up();
}

void rekordbox_pdb_t::page_t::_clean_up() {
    if (m_next_page) {
        delete m_next_page; m_next_page = 0;
    }
    if (!n_heap) {
    }
    if (f_row_groups && !n_row_groups) {
        if (m_row_groups) {
            for (std::vector<row_group_t*>::iterator it = m_row_groups->begin(); it != m_row_groups->end(); ++it) {
                delete *it;
            }
            delete m_row_groups; m_row_groups = 0;
        }
    }
}

uint16_t rekordbox_pdb_t::page_t::num_rows() {
    if (f_num_rows)
        return m_num_rows;
    m_num_rows = (( ((num_rows_large() > num_rows_small()) && (num_rows_large() != 8191)) ) ? (num_rows_large()) : (num_rows_small()));
    f_num_rows = true;
    return m_num_rows;
}

int32_t rekordbox_pdb_t::page_t::num_groups() {
    if (f_num_groups)
        return m_num_groups;
    m_num_groups = (((num_rows() - 1) / 16) + 1);
    f_num_groups = true;
    return m_num_groups;
}

std::vector<rekordbox_pdb_t::row_group_t*>* rekordbox_pdb_t::page_t::row_groups() {
    if (f_row_groups)
        return m_row_groups;
    n_row_groups = true;
    if (is_data_page()) {
        n_row_groups = false;
        int l_row_groups = num_groups();
        m_row_groups = new std::vector<row_group_t*>();
        m_row_groups->reserve(l_row_groups);
        for (int i = 0; i < l_row_groups; i++) {
            m_row_groups->push_back(new row_group_t(i, m__io, this, m__root));
        }
        f_row_groups = true;
    }
    return m_row_groups;
}

int32_t rekordbox_pdb_t::page_t::heap_pos() {
    if (f_heap_pos)
        return m_heap_pos;
    m_heap_pos = _io()->pos();
    f_heap_pos = true;
    return m_heap_pos;
}

bool rekordbox_pdb_t::page_t::is_data_page() {
    if (f_is_data_page)
        return m_is_data_page;
    m_is_data_page = (page_flags() & 64) == 0;
    f_is_data_page = true;
    return m_is_data_page;
}

rekordbox_pdb_t::row_group_t::row_group_t(uint16_t p_group_index, kaitai::kstream* p__io, rekordbox_pdb_t::page_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_group_index = p_group_index;
    m_rows = 0;
    f_base = false;
    f_row_present_flags = false;
    f_rows = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::row_group_t::_read() {
}

rekordbox_pdb_t::row_group_t::~row_group_t() {
    _clean_up();
}

void rekordbox_pdb_t::row_group_t::_clean_up() {
    if (f_row_present_flags) {
    }
    if (f_rows) {
        if (m_rows) {
            for (std::vector<row_ref_t*>::iterator it = m_rows->begin(); it != m_rows->end(); ++it) {
                delete *it;
            }
            delete m_rows; m_rows = 0;
        }
    }
}

int32_t rekordbox_pdb_t::row_group_t::base() {
    if (f_base)
        return m_base;
    m_base = (_root()->len_page() - (group_index() * 36));
    f_base = true;
    return m_base;
}

uint16_t rekordbox_pdb_t::row_group_t::row_present_flags() {
    if (f_row_present_flags)
        return m_row_present_flags;
    std::streampos _pos = m__io->pos();
    m__io->seek((base() - 4));
    m_row_present_flags = m__io->read_u2le();
    m__io->seek(_pos);
    f_row_present_flags = true;
    return m_row_present_flags;
}

std::vector<rekordbox_pdb_t::row_ref_t*>* rekordbox_pdb_t::row_group_t::rows() {
    if (f_rows)
        return m_rows;
    int l_rows = ((group_index() < (_parent()->num_groups() - 1)) ? (16) : ((kaitai::kstream::mod((_parent()->num_rows() - 1), 16) + 1)));
    m_rows = new std::vector<row_ref_t*>();
    m_rows->reserve(l_rows);
    for (int i = 0; i < l_rows; i++) {
        m_rows->push_back(new row_ref_t(i, m__io, this, m__root));
    }
    f_rows = true;
    return m_rows;
}

rekordbox_pdb_t::genre_row_t::genre_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::genre_row_t::_read() {
    m_id = m__io->read_u4le();
    m_name = new device_sql_string_t(m__io, this, m__root);
}

rekordbox_pdb_t::genre_row_t::~genre_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::genre_row_t::_clean_up() {
    if (m_name) {
        delete m_name; m_name = 0;
    }
}

rekordbox_pdb_t::history_entry_row_t::history_entry_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::history_entry_row_t::_read() {
    m_track_id = m__io->read_u4le();
    m_playlist_id = m__io->read_u4le();
    m_entry_index = m__io->read_u4le();
}

rekordbox_pdb_t::history_entry_row_t::~history_entry_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::history_entry_row_t::_clean_up() {
}

rekordbox_pdb_t::artwork_row_t::artwork_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_path = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::artwork_row_t::_read() {
    m_id = m__io->read_u4le();
    m_path = new device_sql_string_t(m__io, this, m__root);
}

rekordbox_pdb_t::artwork_row_t::~artwork_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::artwork_row_t::_clean_up() {
    if (m_path) {
        delete m_path; m_path = 0;
    }
}

rekordbox_pdb_t::device_sql_long_ascii_t::device_sql_long_ascii_t(kaitai::kstream* p__io, rekordbox_pdb_t::device_sql_string_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::device_sql_long_ascii_t::_read() {
    m_length = m__io->read_u2le();
    m__unnamed1 = m__io->read_u1();
    m_text = kaitai::kstream::bytes_to_str(m__io->read_bytes((length() - 4)), std::string("ascii"));
}

rekordbox_pdb_t::device_sql_long_ascii_t::~device_sql_long_ascii_t() {
    _clean_up();
}

void rekordbox_pdb_t::device_sql_long_ascii_t::_clean_up() {
}

rekordbox_pdb_t::artist_row_t::artist_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;
    f_ofs_name_far = false;
    f_name = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::artist_row_t::_read() {
    m_subtype = m__io->read_u2le();
    m_index_shift = m__io->read_u2le();
    m_id = m__io->read_u4le();
    m__unnamed3 = m__io->read_u1();
    m_ofs_name_near = m__io->read_u1();
}

rekordbox_pdb_t::artist_row_t::~artist_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::artist_row_t::_clean_up() {
    if (f_ofs_name_far && !n_ofs_name_far) {
    }
    if (f_name) {
        if (m_name) {
            delete m_name; m_name = 0;
        }
    }
}

uint16_t rekordbox_pdb_t::artist_row_t::ofs_name_far() {
    if (f_ofs_name_far)
        return m_ofs_name_far;
    n_ofs_name_far = true;
    if (subtype() == 100) {
        n_ofs_name_far = false;
        std::streampos _pos = m__io->pos();
        m__io->seek((_parent()->row_base() + 10));
        m_ofs_name_far = m__io->read_u2le();
        m__io->seek(_pos);
        f_ofs_name_far = true;
    }
    return m_ofs_name_far;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::artist_row_t::name() {
    if (f_name)
        return m_name;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ((subtype() == 100) ? (ofs_name_far()) : (ofs_name_near()))));
    m_name = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_name = true;
    return m_name;
}

rekordbox_pdb_t::page_ref_t::page_ref_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_body = 0;
    m__io__raw_body = 0;
    f_body = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::page_ref_t::_read() {
    m_index = m__io->read_u4le();
}

rekordbox_pdb_t::page_ref_t::~page_ref_t() {
    _clean_up();
}

void rekordbox_pdb_t::page_ref_t::_clean_up() {
    if (f_body) {
        if (m__io__raw_body) {
            delete m__io__raw_body; m__io__raw_body = 0;
        }
        if (m_body) {
            delete m_body; m_body = 0;
        }
    }
}

rekordbox_pdb_t::page_t* rekordbox_pdb_t::page_ref_t::body() {
    if (f_body)
        return m_body;
    kaitai::kstream *io = _root()->_io();
    std::streampos _pos = io->pos();
    io->seek((_root()->len_page() * index()));
    m__raw_body = io->read_bytes(_root()->len_page());
    m__io__raw_body = new kaitai::kstream(m__raw_body);
    m_body = new page_t(m__io__raw_body, this, m__root);
    io->seek(_pos);
    f_body = true;
    return m_body;
}

rekordbox_pdb_t::track_row_t::track_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_ofs_strings = 0;
    m_unknown_string_8 = 0;
    m_unknown_string_6 = 0;
    m_analyze_date = 0;
    m_file_path = 0;
    m_autoload_hotcues = 0;
    m_date_added = 0;
    m_unknown_string_3 = 0;
    m_texter = 0;
    m_kuvo_public = 0;
    m_mix_name = 0;
    m_unknown_string_5 = 0;
    m_unknown_string_4 = 0;
    m_message = 0;
    m_unknown_string_2 = 0;
    m_isrc = 0;
    m_unknown_string_7 = 0;
    m_filename = 0;
    m_analyze_path = 0;
    m_comment = 0;
    m_release_date = 0;
    m_title = 0;
    f_unknown_string_8 = false;
    f_unknown_string_6 = false;
    f_analyze_date = false;
    f_file_path = false;
    f_autoload_hotcues = false;
    f_date_added = false;
    f_unknown_string_3 = false;
    f_texter = false;
    f_kuvo_public = false;
    f_mix_name = false;
    f_unknown_string_5 = false;
    f_unknown_string_4 = false;
    f_message = false;
    f_unknown_string_2 = false;
    f_isrc = false;
    f_unknown_string_7 = false;
    f_filename = false;
    f_analyze_path = false;
    f_comment = false;
    f_release_date = false;
    f_title = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::track_row_t::_read() {
    m__unnamed0 = m__io->read_u2le();
    m_index_shift = m__io->read_u2le();
    m_bitmask = m__io->read_u4le();
    m_sample_rate = m__io->read_u4le();
    m_composer_id = m__io->read_u4le();
    m_file_size = m__io->read_u4le();
    m__unnamed6 = m__io->read_u4le();
    m__unnamed7 = m__io->read_u2le();
    m__unnamed8 = m__io->read_u2le();
    m_artwork_id = m__io->read_u4le();
    m_key_id = m__io->read_u4le();
    m_original_artist_id = m__io->read_u4le();
    m_label_id = m__io->read_u4le();
    m_remixer_id = m__io->read_u4le();
    m_bitrate = m__io->read_u4le();
    m_track_number = m__io->read_u4le();
    m_tempo = m__io->read_u4le();
    m_genre_id = m__io->read_u4le();
    m_album_id = m__io->read_u4le();
    m_artist_id = m__io->read_u4le();
    m_id = m__io->read_u4le();
    m_disc_number = m__io->read_u2le();
    m_play_count = m__io->read_u2le();
    m_year = m__io->read_u2le();
    m_sample_depth = m__io->read_u2le();
    m_duration = m__io->read_u2le();
    m__unnamed26 = m__io->read_u2le();
    m_color_id = m__io->read_u1();
    m_rating = m__io->read_u1();
    m__unnamed29 = m__io->read_u2le();
    m__unnamed30 = m__io->read_u2le();
    int l_ofs_strings = 21;
    m_ofs_strings = new std::vector<uint16_t>();
    m_ofs_strings->reserve(l_ofs_strings);
    for (int i = 0; i < l_ofs_strings; i++) {
        m_ofs_strings->push_back(m__io->read_u2le());
    }
}

rekordbox_pdb_t::track_row_t::~track_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::track_row_t::_clean_up() {
    if (m_ofs_strings) {
        delete m_ofs_strings; m_ofs_strings = 0;
    }
    if (f_unknown_string_8) {
        if (m_unknown_string_8) {
            delete m_unknown_string_8; m_unknown_string_8 = 0;
        }
    }
    if (f_unknown_string_6) {
        if (m_unknown_string_6) {
            delete m_unknown_string_6; m_unknown_string_6 = 0;
        }
    }
    if (f_analyze_date) {
        if (m_analyze_date) {
            delete m_analyze_date; m_analyze_date = 0;
        }
    }
    if (f_file_path) {
        if (m_file_path) {
            delete m_file_path; m_file_path = 0;
        }
    }
    if (f_autoload_hotcues) {
        if (m_autoload_hotcues) {
            delete m_autoload_hotcues; m_autoload_hotcues = 0;
        }
    }
    if (f_date_added) {
        if (m_date_added) {
            delete m_date_added; m_date_added = 0;
        }
    }
    if (f_unknown_string_3) {
        if (m_unknown_string_3) {
            delete m_unknown_string_3; m_unknown_string_3 = 0;
        }
    }
    if (f_texter) {
        if (m_texter) {
            delete m_texter; m_texter = 0;
        }
    }
    if (f_kuvo_public) {
        if (m_kuvo_public) {
            delete m_kuvo_public; m_kuvo_public = 0;
        }
    }
    if (f_mix_name) {
        if (m_mix_name) {
            delete m_mix_name; m_mix_name = 0;
        }
    }
    if (f_unknown_string_5) {
        if (m_unknown_string_5) {
            delete m_unknown_string_5; m_unknown_string_5 = 0;
        }
    }
    if (f_unknown_string_4) {
        if (m_unknown_string_4) {
            delete m_unknown_string_4; m_unknown_string_4 = 0;
        }
    }
    if (f_message) {
        if (m_message) {
            delete m_message; m_message = 0;
        }
    }
    if (f_unknown_string_2) {
        if (m_unknown_string_2) {
            delete m_unknown_string_2; m_unknown_string_2 = 0;
        }
    }
    if (f_isrc) {
        if (m_isrc) {
            delete m_isrc; m_isrc = 0;
        }
    }
    if (f_unknown_string_7) {
        if (m_unknown_string_7) {
            delete m_unknown_string_7; m_unknown_string_7 = 0;
        }
    }
    if (f_filename) {
        if (m_filename) {
            delete m_filename; m_filename = 0;
        }
    }
    if (f_analyze_path) {
        if (m_analyze_path) {
            delete m_analyze_path; m_analyze_path = 0;
        }
    }
    if (f_comment) {
        if (m_comment) {
            delete m_comment; m_comment = 0;
        }
    }
    if (f_release_date) {
        if (m_release_date) {
            delete m_release_date; m_release_date = 0;
        }
    }
    if (f_title) {
        if (m_title) {
            delete m_title; m_title = 0;
        }
    }
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::unknown_string_8() {
    if (f_unknown_string_8)
        return m_unknown_string_8;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(18)));
    m_unknown_string_8 = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_unknown_string_8 = true;
    return m_unknown_string_8;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::unknown_string_6() {
    if (f_unknown_string_6)
        return m_unknown_string_6;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(9)));
    m_unknown_string_6 = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_unknown_string_6 = true;
    return m_unknown_string_6;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::analyze_date() {
    if (f_analyze_date)
        return m_analyze_date;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(15)));
    m_analyze_date = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_analyze_date = true;
    return m_analyze_date;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::file_path() {
    if (f_file_path)
        return m_file_path;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(20)));
    m_file_path = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_file_path = true;
    return m_file_path;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::autoload_hotcues() {
    if (f_autoload_hotcues)
        return m_autoload_hotcues;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(7)));
    m_autoload_hotcues = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_autoload_hotcues = true;
    return m_autoload_hotcues;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::date_added() {
    if (f_date_added)
        return m_date_added;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(10)));
    m_date_added = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_date_added = true;
    return m_date_added;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::unknown_string_3() {
    if (f_unknown_string_3)
        return m_unknown_string_3;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(3)));
    m_unknown_string_3 = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_unknown_string_3 = true;
    return m_unknown_string_3;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::texter() {
    if (f_texter)
        return m_texter;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(1)));
    m_texter = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_texter = true;
    return m_texter;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::kuvo_public() {
    if (f_kuvo_public)
        return m_kuvo_public;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(6)));
    m_kuvo_public = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_kuvo_public = true;
    return m_kuvo_public;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::mix_name() {
    if (f_mix_name)
        return m_mix_name;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(12)));
    m_mix_name = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_mix_name = true;
    return m_mix_name;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::unknown_string_5() {
    if (f_unknown_string_5)
        return m_unknown_string_5;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(8)));
    m_unknown_string_5 = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_unknown_string_5 = true;
    return m_unknown_string_5;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::unknown_string_4() {
    if (f_unknown_string_4)
        return m_unknown_string_4;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(4)));
    m_unknown_string_4 = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_unknown_string_4 = true;
    return m_unknown_string_4;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::message() {
    if (f_message)
        return m_message;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(5)));
    m_message = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_message = true;
    return m_message;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::unknown_string_2() {
    if (f_unknown_string_2)
        return m_unknown_string_2;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(2)));
    m_unknown_string_2 = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_unknown_string_2 = true;
    return m_unknown_string_2;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::isrc() {
    if (f_isrc)
        return m_isrc;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(0)));
    m_isrc = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_isrc = true;
    return m_isrc;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::unknown_string_7() {
    if (f_unknown_string_7)
        return m_unknown_string_7;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(13)));
    m_unknown_string_7 = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_unknown_string_7 = true;
    return m_unknown_string_7;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::filename() {
    if (f_filename)
        return m_filename;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(19)));
    m_filename = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_filename = true;
    return m_filename;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::analyze_path() {
    if (f_analyze_path)
        return m_analyze_path;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(14)));
    m_analyze_path = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_analyze_path = true;
    return m_analyze_path;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::comment() {
    if (f_comment)
        return m_comment;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(16)));
    m_comment = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_comment = true;
    return m_comment;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::release_date() {
    if (f_release_date)
        return m_release_date;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(11)));
    m_release_date = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_release_date = true;
    return m_release_date;
}

rekordbox_pdb_t::device_sql_string_t* rekordbox_pdb_t::track_row_t::title() {
    if (f_title)
        return m_title;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->row_base() + ofs_strings()->at(17)));
    m_title = new device_sql_string_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_title = true;
    return m_title;
}

rekordbox_pdb_t::key_row_t::key_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::key_row_t::_read() {
    m_id = m__io->read_u4le();
    m_id2 = m__io->read_u4le();
    m_name = new device_sql_string_t(m__io, this, m__root);
}

rekordbox_pdb_t::key_row_t::~key_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::key_row_t::_clean_up() {
    if (m_name) {
        delete m_name; m_name = 0;
    }
}

rekordbox_pdb_t::playlist_entry_row_t::playlist_entry_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::playlist_entry_row_t::_read() {
    m_entry_index = m__io->read_u4le();
    m_track_id = m__io->read_u4le();
    m_playlist_id = m__io->read_u4le();
}

rekordbox_pdb_t::playlist_entry_row_t::~playlist_entry_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::playlist_entry_row_t::_clean_up() {
}

rekordbox_pdb_t::label_row_t::label_row_t(kaitai::kstream* p__io, rekordbox_pdb_t::row_ref_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::label_row_t::_read() {
    m_id = m__io->read_u4le();
    m_name = new device_sql_string_t(m__io, this, m__root);
}

rekordbox_pdb_t::label_row_t::~label_row_t() {
    _clean_up();
}

void rekordbox_pdb_t::label_row_t::_clean_up() {
    if (m_name) {
        delete m_name; m_name = 0;
    }
}

rekordbox_pdb_t::device_sql_long_utf16le_t::device_sql_long_utf16le_t(kaitai::kstream* p__io, rekordbox_pdb_t::device_sql_string_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::device_sql_long_utf16le_t::_read() {
    m_length = m__io->read_u2le();
    m__unnamed1 = m__io->read_u1();
    m_text = kaitai::kstream::bytes_to_str(m__io->read_bytes((length() - 4)), std::string("utf-16le"));
}

rekordbox_pdb_t::device_sql_long_utf16le_t::~device_sql_long_utf16le_t() {
    _clean_up();
}

void rekordbox_pdb_t::device_sql_long_utf16le_t::_clean_up() {
}

rekordbox_pdb_t::table_t::table_t(kaitai::kstream* p__io, rekordbox_pdb_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_first_page = 0;
    m_last_page = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::table_t::_read() {
    m_type = static_cast<rekordbox_pdb_t::page_type_t>(m__io->read_u4le());
    m_empty_candidate = m__io->read_u4le();
    m_first_page = new page_ref_t(m__io, this, m__root);
    m_last_page = new page_ref_t(m__io, this, m__root);
}

rekordbox_pdb_t::table_t::~table_t() {
    _clean_up();
}

void rekordbox_pdb_t::table_t::_clean_up() {
    if (m_first_page) {
        delete m_first_page; m_first_page = 0;
    }
    if (m_last_page) {
        delete m_last_page; m_last_page = 0;
    }
}

rekordbox_pdb_t::row_ref_t::row_ref_t(uint16_t p_row_index, kaitai::kstream* p__io, rekordbox_pdb_t::row_group_t* p__parent, rekordbox_pdb_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_row_index = p_row_index;
    f_ofs_row = false;
    f_row_base = false;
    f_present = false;
    f_body = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void rekordbox_pdb_t::row_ref_t::_read() {
}

rekordbox_pdb_t::row_ref_t::~row_ref_t() {
    _clean_up();
}

void rekordbox_pdb_t::row_ref_t::_clean_up() {
    if (f_ofs_row) {
    }
    if (f_body && !n_body) {
        if (m_body) {
            delete m_body; m_body = 0;
        }
    }
}

uint16_t rekordbox_pdb_t::row_ref_t::ofs_row() {
    if (f_ofs_row)
        return m_ofs_row;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->base() - (6 + (2 * row_index()))));
    m_ofs_row = m__io->read_u2le();
    m__io->seek(_pos);
    f_ofs_row = true;
    return m_ofs_row;
}

int32_t rekordbox_pdb_t::row_ref_t::row_base() {
    if (f_row_base)
        return m_row_base;
    m_row_base = (ofs_row() + _parent()->_parent()->heap_pos());
    f_row_base = true;
    return m_row_base;
}

bool rekordbox_pdb_t::row_ref_t::present() {
    if (f_present)
        return m_present;
    m_present = ((((_parent()->row_present_flags() >> row_index()) & 1) != 0) ? (true) : (false));
    f_present = true;
    return m_present;
}

kaitai::kstruct* rekordbox_pdb_t::row_ref_t::body() {
    if (f_body)
        return m_body;
    n_body = true;
    if (present()) {
        n_body = false;
        std::streampos _pos = m__io->pos();
        m__io->seek(row_base());
        n_body = true;
        switch (_parent()->_parent()->type()) {
        case rekordbox_pdb_t::PAGE_TYPE_PLAYLIST_TREE: {
            n_body = false;
            m_body = new playlist_tree_row_t(m__io, this, m__root);
            break;
        }
        case rekordbox_pdb_t::PAGE_TYPE_KEYS: {
            n_body = false;
            m_body = new key_row_t(m__io, this, m__root);
            break;
        }
        case rekordbox_pdb_t::PAGE_TYPE_ARTISTS: {
            n_body = false;
            m_body = new artist_row_t(m__io, this, m__root);
            break;
        }
        case rekordbox_pdb_t::PAGE_TYPE_ALBUMS: {
            n_body = false;
            m_body = new album_row_t(m__io, this, m__root);
            break;
        }
        case rekordbox_pdb_t::PAGE_TYPE_GENRES: {
            n_body = false;
            m_body = new genre_row_t(m__io, this, m__root);
            break;
        }
        case rekordbox_pdb_t::PAGE_TYPE_HISTORY_PLAYLISTS: {
            n_body = false;
            m_body = new history_playlist_row_t(m__io, this, m__root);
            break;
        }
        case rekordbox_pdb_t::PAGE_TYPE_ARTWORK: {
            n_body = false;
            m_body = new artwork_row_t(m__io, this, m__root);
            break;
        }
        case rekordbox_pdb_t::PAGE_TYPE_PLAYLIST_ENTRIES: {
            n_body = false;
            m_body = new playlist_entry_row_t(m__io, this, m__root);
            break;
        }
        case rekordbox_pdb_t::PAGE_TYPE_LABELS: {
            n_body = false;
            m_body = new label_row_t(m__io, this, m__root);
            break;
        }
        case rekordbox_pdb_t::PAGE_TYPE_TRACKS: {
            n_body = false;
            m_body = new track_row_t(m__io, this, m__root);
            break;
        }
        case rekordbox_pdb_t::PAGE_TYPE_HISTORY_ENTRIES: {
            n_body = false;
            m_body = new history_entry_row_t(m__io, this, m__root);
            break;
        }
        case rekordbox_pdb_t::PAGE_TYPE_COLORS: {
            n_body = false;
            m_body = new color_row_t(m__io, this, m__root);
            break;
        }
        }
        m__io->seek(_pos);
        f_body = true;
    }
    return m_body;
}
