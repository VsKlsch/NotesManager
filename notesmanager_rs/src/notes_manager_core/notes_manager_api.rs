use unsafe_notes_manager_core::{CryptedNote, CryptedNote_Destroy, DecryptedNote, DecryptedNote_Destroy, NotesManagerAPI, NotesManagerAPI_Destroy, NotesManagerAPI_Init};

mod unsafe_notes_manager_core;

pub struct NotesMangerAPISafe{
    unsafe_api: *mut NotesManagerAPI,
}

pub struct CryptedNoteSafe{
    unsafe_crypted_note: *mut CryptedNote
}

pub struct DecryptedNoteSafe{
    unsafe_decrypted_note: *mut DecryptedNote
}

impl NotesMangerAPISafe{
    pub fn new() -> Option<NotesMangerAPISafe>{
        let api = unsafe { NotesManagerAPI_Init() };
        if api != std::ptr::null_mut(){
            Some(NotesMangerAPISafe{unsafe_api: api})
        }else{
            None
        }
    }

    pub fn get_all_notes(&self) -> Vec<CryptedNoteSafe>{

        vec![]
    }
}

impl CryptedNoteSafe{
    pub fn decrypt(&self, password: String) -> Option<DecryptedNoteSafe>{
        None
    }
}

impl DecryptedNoteSafe{
    pub fn get_title(&self) -> String{
        String::from("")
    }
}

impl Drop for NotesMangerAPISafe{
    fn drop(&mut self){
        if self.unsafe_api != std::ptr::null_mut(){
            unsafe { NotesManagerAPI_Destroy(self.unsafe_api) };
        } 
    }
}

impl Drop for CryptedNoteSafe{
    fn drop(&mut self){
        if self.unsafe_crypted_note != std::ptr::null_mut(){
            unsafe { CryptedNote_Destroy(self.unsafe_crypted_note) };
        }
    }
}

impl Drop for DecryptedNoteSafe{
    fn drop(&mut self){
        if self.unsafe_decrypted_note != std::ptr::null_mut(){
            unsafe { DecryptedNote_Destroy(self.unsafe_decrypted_note) };
        }
    }
}