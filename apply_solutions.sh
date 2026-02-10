#!/bin/bash
# apply_solutions.sh - Copy reference solutions to starter folders
#
# This script copies solution files to starter folders for sessions that have
# solutions available. Use this if you want to see the reference implementation
# or if you're stuck and want to move forward.
#
# Usage: ./apply_solutions.sh [session_number]
#   Without arguments: Applies all available solutions
#   With session number: Applies only that session's solution (e.g., ./apply_solutions.sh 1)

set -e

SESSIONS_DIR="sessions"

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

apply_solution() {
    local session_dir=$1
    local session_name=$(basename "$session_dir")
    local solution_dir="$session_dir/solution"
    local starter_dir="$session_dir/starter"
    
    if [ ! -d "$solution_dir" ]; then
        return 0  # Skip silently if no solution folder
    fi
    
    if [ ! -d "$starter_dir" ]; then
        echo -e "${RED}✗ No starter folder found for $session_name${NC}"
        return 1
    fi
    
    echo -e "${YELLOW}Applying solution for $session_name...${NC}"
    
    # Copy all files from solution to starter
    local file_count=0
    for file in "$solution_dir"/*; do
        if [ -f "$file" ]; then
            local filename=$(basename "$file")
            cp "$file" "$starter_dir/"
            echo -e "  ${GREEN}✓${NC} Copied $filename"
            ((file_count++))
        fi
    done
    
    if [ $file_count -eq 0 ]; then
        echo -e "  ${YELLOW}⚠${NC} No files found in solution folder"
    else
        echo -e "${GREEN}✓ Applied $file_count file(s) for $session_name${NC}"
    fi
    echo
}

# Main logic
if [ $# -eq 0 ]; then
    # Apply all available solutions
    echo -e "${YELLOW}Applying all available solutions...${NC}"
    echo
    
    applied_count=0
    for session_dir in "$SESSIONS_DIR"/*/; do
        if [ -d "$session_dir" ]; then
            if apply_solution "$session_dir"; then
                if [ -d "$session_dir/solution" ]; then
                    ((applied_count++))
                fi
            fi
        fi
    done
    
    if [ $applied_count -eq 0 ]; then
        echo -e "${YELLOW}No solutions available yet.${NC}"
    else
        echo -e "${GREEN}✓ Applied solutions for $applied_count session(s)${NC}"
    fi
else
    # Apply specific session solution
    session_num=$(printf "%02d" $1)
    found=0
    
    for session_dir in "$SESSIONS_DIR"/${session_num}_*/; do
        if [ -d "$session_dir" ]; then
            found=1
            apply_solution "$session_dir"
            break
        fi
    done
    
    if [ $found -eq 0 ]; then
        echo -e "${RED}✗ Session $1 not found${NC}"
        exit 1
    fi
fi

echo -e "${GREEN}Done!${NC}"
echo -e "${YELLOW}Note: You can restore starter files with: git checkout sessions/*/starter/${NC}"
