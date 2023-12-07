#[macro_use] extern crate rocket;

use rand::seq::IteratorRandom;
use std::fs;
use rocket::fs::{FileServer, NamedFile};

#[get("/")]
async fn home() -> Option<NamedFile> {
    NamedFile::open("static/index.html").await.ok()
}

#[get("/radio")]
async fn radio() -> Option<NamedFile> {
    NamedFile::open(randomfile("./tunes")).await.ok()
}

#[catch(404)]
async fn not_found() -> Option<NamedFile> {
    NamedFile::open("static/404.html").await.ok()
}

#[launch]
fn rocket() -> _ {
    rocket::build()
    .register("/", catchers![not_found])
    .mount("/", routes![home, radio])
    .mount("/", FileServer::from("static/"))
    .mount("/share", FileServer::from("share/").rank(2))
}

fn randomfile(path: &str) -> String {
    let mut rng = rand::thread_rng();
    let files = fs::read_dir(path).unwrap();
    let file = files.choose(&mut rng).unwrap().unwrap();
    file.path().display().to_string()
}
