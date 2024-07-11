mod notes_manager_core;

fn main() {
    if let Some(_api) = notes_manager_core::NotesMangerAPISafe::new(){
        println!("Notes manager api initialized");
    }
}
