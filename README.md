# MP3 Tag Reader & Editor (C Project)

A simple and efficient **MP3 Tag Reader and Editor** implemented in **C programming language**.
This project reads and modifies **ID3v2.3 MP3 metadata**, such as:

* Title
* Artist
* Album
* Year
* Genre
* Comment
* Track number

It helps understand **file handling**, **bit manipulation**, and **ID3 metadata format** in MP3 files.

---

## 📌 Features

### ✔ MP3 Tag Reader

* Extracts ID3v2.3 metadata from any `.mp3` file
* Displays all major fields in a clean format
* Validates ID3 header and supported frames
* Error handling for invalid files or missing tags

### ✔ MP3 Tag Editor

* Edit and update specific tags (Title, Artist, Album, etc.)
* Write changes back into the file without corrupting audio data
* Preserves the original file structure and padding
* Safe writing with checks on frame sizes

---

## 📁 Project Structure

```
├── main.c
├── id3.h
├── id3.c
├── error_handling.h
├── error_handling.c
├── Makefile
└── sample.mp3     (optional test file)
```

---

## 🛠 How to Build

### Using Makefile

```
make
```

### Without Makefile

```
gcc main.c id3.c error_handling.c -o mp3_tag_editor
```

---

## ▶️ How to Run

### 1. View MP3 Tags

```
./mp3_tag_editor -v <mp3_filename>
```

Example:

```
./mp3_tag_editor -v song.mp3
```

### 2. Edit a Tag

```
./mp3_tag_editor -e <tag_name> <new_value> <mp3_filename>
```

Example (change title):

```
./mp3_tag_editor -e title "My New Song" song.mp3
```

Supported tag names:

```
title, artist, album, year, genre, comment, track
```

---

## 📚 Concepts Used

* File I/O (fopen, fread, fwrite, fseek)
* Structs and metadata parsing
* Bit-level operations
* Endianness handling
* Memory management
* ID3v2.3 frame structure

---

## 🧪 Sample Output (View Tags)

```
Title   : Shape of You
Artist  : Ed Sheeran
Album   : Divide
Year    : 2017
Genre   : Pop
Comment : -
Track   : 1
```

---

## ⚠️ Limitations

* Supports only **ID3v2.3** tags
* Does not decode audio data
* Editing increases frame size only if padding is available

---

## 🚀 Future Improvements

* Support for ID3v1 & ID3v2.4
* GUI-based tag editor
* Batch editing for multiple MP3 files

---

## 📝 License

This project is open-source under the **MIT License**.
Feel free to use, modify, and contribute!

---

## 👨‍💻 Author

**Prashanth Reddy**
Embedded Systems Student – Emertxe
GitHub: https://github.com/Prashanth2445
