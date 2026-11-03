#!/usr/bin/env python3
"""
IMDb Dataset Fetcher & Preprocessor for CineSort
Course: COP3530 Project 2b (Group 99)

Downloads official IMDb non-commercial datasets:
- title.basics.tsv.gz
- title.ratings.tsv.gz

Merges them on 'tconst' and produces 'movies_cleaned.tsv' containing >= 100,000
valid movie records with non-null Year, Runtime, and Votes.
"""

import gzip
import os
import urllib.request
import csv

DATA_DIR = os.path.dirname(os.path.abspath(__file__))
BASICS_URL = "https://datasets.imdbws.com/title.basics.tsv.gz"
RATINGS_URL = "https://datasets.imdbws.com/title.ratings.tsv.gz"

BASICS_GZ = os.path.join(DATA_DIR, "title.basics.tsv.gz")
RATINGS_GZ = os.path.join(DATA_DIR, "title.ratings.tsv.gz")
OUTPUT_TSV = os.path.join(DATA_DIR, "movies_cleaned.tsv")

TARGET_ROW_COUNT = 120000

def download_file(url, target_path):
    if os.path.exists(target_path):
        print(f"[Cache] {os.path.basename(target_path)} already exists.")
        return
    print(f"[Download] Fetching {url} ...")
    urllib.request.urlretrieve(url, target_path)
    print(f"[Download] Finished {os.path.basename(target_path)}.")

def process_datasets():
    download_file(BASICS_URL, BASICS_GZ)
    download_file(RATINGS_URL, RATINGS_GZ)

    print("[Process] Reading ratings into memory...")
    ratings = {} # tconst -> numVotes
    with gzip.open(RATINGS_GZ, 'rt', encoding='utf-8') as f:
        reader = csv.reader(f, delimiter='\t')
        header = next(reader, None)
        for row in reader:
            if len(row) >= 3:
                tconst = row[0]
                num_votes = row[2]
                if num_votes.isdigit():
                    ratings[tconst] = int(num_votes)

    print(f"[Process] Loaded {len(ratings):,} rating entries.")
    print(f"[Process] Filtering movie records to produce {OUTPUT_TSV} (Target >= {TARGET_ROW_COUNT:,} rows)...")

    valid_rows = []
    with gzip.open(BASICS_GZ, 'rt', encoding='utf-8') as f:
        reader = csv.reader(f, delimiter='\t')
        header = next(reader, None)
        # titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres
        for row in reader:
            if len(row) < 9:
                continue
            tconst = row[0]
            title_type = row[1]
            primary_title = row[2]
            start_year = row[5]
            runtime_minutes = row[7]

            # We focus on movies with valid integers
            if title_type in ('movie', 'tvMovie') and start_year.isdigit() and runtime_minutes.isdigit():
                if tconst in ratings:
                    votes = ratings[tconst]
                    valid_rows.append([tconst, primary_title, start_year, runtime_minutes, str(votes)])
                    if len(valid_rows) >= TARGET_ROW_COUNT:
                        break

    print(f"[Process] Writing {len(valid_rows):,} rows to {OUTPUT_TSV}...")
    with open(OUTPUT_TSV, 'w', encoding='utf-8', newline='') as f:
        writer = csv.writer(f, delimiter='\t')
        writer.writerow(["tconst", "primaryTitle", "startYear", "runtimeMinutes", "numVotes"])
        writer.writerows(valid_rows)

    print(f"[Success] Created {OUTPUT_TSV} with {len(valid_rows):,} valid rows!")

if __name__ == "__main__":
    process_datasets()
