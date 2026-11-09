# Moviest - A Movie Ranker
## Team Members
- Natania Philippe (Blakesuga)
- Tamer Sabry (tamer-sabry)
- Brett Raimann (raimannb-stack and alsodeonhart530 in commits, not sure why GitHub changed his username at times)

## Notes
- Do not edit the raw dataset. All filtering and manipulation of data must be done through code to avoid corruption of data and unwanted behavior

## Instructions on running project

After cloning this repository, make sure you change directories so that your terminal is working within the root directory of this project.

**Step 1** - Go to https://www.kaggle.com/datasets/asaniczka/tmdb-movies-dataset-2023-930k-movies and download `TMDB_movie_dataset_v11.csv`

**Step 2** - Within the root directory of the project (the one with CMakeLists.txt), create a new directory named data
```powershell
mkdir 'data'
```
**Step 3** - Move `TMDB_movie_dataset_v11.csv` into the data directory, and rename it EXACTLY to `kaggle_movie_dataset.csv`

**Step 4** - Depending on your system, run the following commands in a terminal in the root directory of this project

**Windows**
```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\MovieRanker.exe 
```
**Mac/Linux**
```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\MovieRanker.exe 
```
