# CineSort Dataset Information

## Requirements
COP3530 requires a dataset with **at least 100,000 records/tuples**.

## Generating the Real IMDb Dataset
Run the pre-configured script to download official IMDb datasets and merge them:
```bash
python data/download_dataset.py
```
This produces `movies_cleaned.tsv` containing **120,000 valid movie records** with the following schema:
- `tconst`: IMDb identifier (e.g., `tt0111161`)
- `primaryTitle`: Title of the movie
- `startYear`: Release year integer
- `runtimeMinutes`: Duration integer
- `numVotes`: Total rating votes integer

## Built-in Fallback
If `movies_cleaned.tsv` is not present, `CineSort` automatically falls back to generating **120,000 synthetic records** so you can compile, test, and benchmark the algorithms immediately without an internet connection.
