use std::env;
use std::path::PathBuf;

fn main(){
    println!("cargo:rustc-link-search=../build/NotesManagerCore");
    println!("cargo:rustc-link-lib=NotesManagerCore");

    let bindings = bindgen::Builder::default()
        .header("wrapper.h")
        // Finish the builder and generate the bindings.
        .generate()
        // Unwrap the Result and panic on failure.
        .expect("Unable to generate bindings");

        let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
        bindings
            .write_to_file(out_path.join("bindings.rs"))
            .expect("Couldn't write bindings!");
}