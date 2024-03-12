#Python 3.11
from mutagen.mp3 import MP3
import os
import math

def get_mp3_lengths(folder_path):
    lengths = []
    files = os.listdir(folder_path)
    files.sort()
    for file_name in files:
        file_path = os.path.join(folder_path, file_name)
        try:
            audio = MP3(file_path)
            length = math.ceil(audio.info.length)
            lengths.append(length)
        except Exception as e:
            print(f"Error processing {file_path}: {e}")
            continue
    return lengths

def get_folder_path():
    while True:
        path = input("Enter path to folder with mp3 files: ")
        if os.path.isdir(path):
            return path
        else:
            print("Invalid path. Please try again.")

print("This is a script for renaming audio files for the DFMiniMp3 module. After its execution, "
      "the names of all files will be numbered, and you will receive an array with the durations of audio files in seconds")

folder_path = get_folder_path()

files = os.listdir(folder_path)
files.sort()
counter = 1
for file_name in files:
    old_path = os.path.join(folder_path, file_name)
    # Extracting the file extension
    file_extension = os.path.splitext(file_name)[1]
    if file_name.endswith(".mp3"):
        new_file_name = "{:04d}-{}{}".format(counter, os.path.splitext(file_name)[0], file_extension)
        new_path = os.path.join(folder_path, new_file_name)
        os.rename(old_path, new_path)
        counter += 1

mp3_lengths = get_mp3_lengths(folder_path)

#Open this code if you want a text file with an array of lengths to be created in the mp3 folder
""""
with open(os.path.join(folder_path, "mp3length.txt"), "w") as file:
    file.write("unsigned long mp3length[] = {" + ", ".join(str(length) for length in mp3_lengths) + "};")
"""

print("unsigned long mp3length[] = {" + ", ".join(str(length) for length in mp3_lengths) + "};")

print("Task completed successfully!")

