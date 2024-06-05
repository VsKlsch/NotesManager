#include <sstream>

#include <private/include/SQLiteDatabaseRepo.hpp>

namespace NotesManager::Repository::SQLite{
    SQLiteRepository::SQLiteRepository(const std::filesystem::path& dbPath){
        static const char query[] = "CREATE TABLE IF NOT EXISTS notes (id INTEGER NOT NULL PRIMARY KEY, algname TEXT NOT NULL, data BLOB NOT NULL, sign BLOB);";
        sqlite3* DB;
        
        int result = sqlite3_open(dbPath.generic_string().c_str(), &DB);
        if(result)
            throw DatabaseException("Database creation Error");
        
        sqlite3_exec(DB, query, nullptr, nullptr, nullptr);
        this->DB = DB;
    }

    SQLiteRepository::~SQLiteRepository(){
        sqlite3_close(this->DB);
    }

    static std::vector<uint8_t> hexstr2bytevec(std::string hexstr){
        std::vector<uint8_t> out;
        out.reserve(hexstr.length()/2);
        for(int i =0; i < hexstr.length(); i+=2){
            std::string byteString = hexstr.substr(i, 2);
            uint8_t byte = (uint8_t)std::strtol(byteString.c_str(), nullptr, 16);
            out.push_back(byte);
        }
        return out;
    }

    static std::string bytevec2hexstr(const std::vector<uint8_t>& bytes){
        std::stringstream outStringStream;

        for (auto el: bytes){
            outStringStream<<std::hex<<(int)el;
        }

        return outStringStream.str();
    }
    
    static int getAllNotesCallback(void* data, int argc, char** argv, char** azColName){
        std::vector<NoteDTO>* dtos = reinterpret_cast<std::vector<NoteDTO>*>(data);
        NoteDTO dto;
        
        for(int i =0; i<argc; ++i){
            std::string colName (azColName[i]);
            if(colName == "id"){
                dto.noteId = std::atoi(argv[i]);
            }else if(colName == "algname"){
                dto.algorithmName = std::string(argv[i]);
            }else if(colName == "data"){
                dto.data = hexstr2bytevec(std::string(argv[i]));
            }else if(colName == "sign"){
                dto.sign = hexstr2bytevec(std::string(argv[i]));
            }
        }
        dtos->push_back(std::move(dto));
        return 0;
    }

    std::vector<NoteDTO> SQLiteRepository::getAllNotes() const{
        static const char query[] = "SELECT id, algname, hex(data) as data, hex(sign) as sign  from notes;";
        std::vector<NoteDTO> dtos;
        sqlite3_exec(this->DB, query, getAllNotesCallback, reinterpret_cast<void*>(&dtos), nullptr);
        return dtos;
    }

    static int getNoteByIdCallback(void* data, int argc, char** argv, char** azColName){
        std::vector<NoteDTO>* dtos = reinterpret_cast<std::vector<NoteDTO>*>(data);
        NoteDTO dto;
        
        for(int i =0; i<argc; ++i){
            std::string colName (azColName[i]);
            if(colName == "id"){
                dto.noteId = std::atoi(argv[i]);
            }else if(colName == "algname"){
                dto.algorithmName = std::string(argv[i]);
            }else if(colName == "data"){
                dto.data = hexstr2bytevec(std::string(argv[i]));
            }else if(colName == "sign"){
                dto.sign = hexstr2bytevec(std::string(argv[i]));
            }
        }
        dtos->push_back(std::move(dto));
        return 0;
    }

    std::optional<NoteDTO> SQLiteRepository::getNoteById(uint32_t id) const{
        std::string query = "SELECT id, algname, hex(data) as data, hex(sign) as sign from notes where id = "+std::to_string(id)+" LIMIT 1 OFFSET 0;";
        std::vector<NoteDTO> dtos;
        sqlite3_exec(this->DB, query.c_str(), getNoteByIdCallback, reinterpret_cast<void*>(&dtos), nullptr);
        if(dtos.size() > 0){
            return std::move(dtos[0]);
        }
        return std::nullopt;
    }

    void SQLiteRepository::insertNote(const NoteDTO& note) const{
        static const std::string query = "INSERT INTO notes (algname, data, sign) VALUES(?,?,?);";
        sqlite3_stmt* stmt;

        sqlite3_prepare( this->DB, query.c_str(), query.length(), &stmt, nullptr );
        sqlite3_bind_text(stmt, 1, note.algorithmName.c_str(), note.algorithmName.length(), SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, reinterpret_cast<const void*>(note.data.data()), note.data.size(), SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 3, reinterpret_cast<const void*>(note.sign.data()), note.sign.size(), SQLITE_STATIC );
        sqlite3_step(stmt);
    }

    void SQLiteRepository::removeNoteById(uint32_t id) const{
        std::string query = "DELETE from notes WHERE id = "+std::to_string(id)+";";
        sqlite3_exec(this->DB, query.c_str(), nullptr, nullptr, nullptr);
    }

    void SQLiteRepository::updateNote(const NoteDTO& note) const{
        static const std::string query = "UPDATE notes SET algname = ?, data = ?, sign = ? WHERE id = ?;";
        sqlite3_stmt* stmt;

        sqlite3_prepare( this->DB, query.c_str(), query.length(), &stmt, nullptr );

        sqlite3_bind_text(stmt, 1, note.algorithmName.c_str(), note.algorithmName.length(), SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, reinterpret_cast<const void*>(note.data.data()), note.data.size(), SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 3, reinterpret_cast<const void*>(note.sign.data()), note.sign.size(), SQLITE_STATIC );
        sqlite3_bind_int(stmt, 4, note.noteId);
        sqlite3_step(stmt);
    }
}
