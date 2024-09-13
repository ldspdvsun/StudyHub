#!/bin/bash
# delete all file like *.out
sudo find $1/ -name "*.out" -delete
sudo find $1/ -name "*.o" -delete
sudo find $1/ -name "*.log" -delete
sudo find "$1" -type d -name ".pytest_cache" -exec rm -rf {} +
sudo find "$1" -type d -name "__pycache__" -exec rm -rf {} +
sudo find "$1" -type d -name ".mypy_cache" -exec rm -rf {} +