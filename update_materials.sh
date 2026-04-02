#!/bin/bash
# update_materials.sh - Get new sessions and updates from the course template
#
# This script helps you safely update your repository with new course materials
# while preserving your work.

set -e

TEMPLATE_REPO="https://github.com/gamesh411/cpp-quest.git"
TEMPLATE_REMOTE="template"

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== C++ Quest Material Updater ===${NC}\n"

# Check if we're in a git repository
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    echo -e "${RED}Error: Not in a git repository${NC}"
    exit 1
fi

# Check for uncommitted changes
if ! git diff-index --quiet HEAD -- 2>/dev/null; then
    echo -e "${YELLOW}Warning: You have uncommitted changes${NC}"
    echo "Please commit or stash your changes before updating."
    echo ""
    git status --short
    echo ""
    read -p "Continue anyway? (y/n) " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

# Add template remote if it doesn't exist
if ! git remote get-url $TEMPLATE_REMOTE > /dev/null 2>&1; then
    echo -e "${YELLOW}Adding template remote...${NC}"
    git remote add $TEMPLATE_REMOTE $TEMPLATE_REPO
fi

# Fetch latest from template
echo -e "${BLUE}Fetching latest updates...${NC}"
git fetch $TEMPLATE_REMOTE

# Check if there are updates
BEHIND=$(git rev-list --count HEAD..$TEMPLATE_REMOTE/main 2>/dev/null || echo "0")

if [ "$BEHIND" = "0" ]; then
    echo -e "${GREEN}✓ You're up to date! No new materials available.${NC}"
    exit 0
fi

# Show what's new
echo -e "\n${GREEN}New updates available:${NC}"
echo -e "${YELLOW}$BEHIND new commit(s)${NC}\n"

git log HEAD..$TEMPLATE_REMOTE/main --oneline --decorate --color=always | head -20

if [ "$BEHIND" -gt 20 ]; then
    echo "... and more"
fi

echo ""

# Show which files will be affected
echo -e "${BLUE}Files that will be updated:${NC}"
git diff --name-status HEAD..$TEMPLATE_REMOTE/main | head -20

echo ""

# Ask to proceed
read -p "Merge these updates? (y/n) " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo -e "${YELLOW}Update cancelled. You can update later by running this script again.${NC}"
    exit 0
fi

# Attempt merge
echo -e "${BLUE}Merging updates...${NC}"

# Use --allow-unrelated-histories for template repos (needed on first update)
if git merge $TEMPLATE_REMOTE/main --allow-unrelated-histories --no-edit; then
    echo -e "\n${GREEN}✓ Successfully updated!${NC}"
    echo -e "${GREEN}✓ New materials are now available in your repository.${NC}"
    
    # Show new sessions if any
    NEW_SESSIONS=$(git diff --name-only HEAD@{1} HEAD | grep "sessions/" | cut -d'/' -f2 | sort -u)
    if [ -n "$NEW_SESSIONS" ]; then
        echo -e "\n${GREEN}New/Updated Sessions:${NC}"
        echo "$NEW_SESSIONS" | while read session; do
            echo -e "  ${GREEN}✓${NC} $session"
        done
    fi
    
    echo -e "\n${BLUE}Next steps:${NC}"
    echo "1. Review the changes: git log --oneline -5"
    echo "2. Rebuild: cd build && cmake .. && make"
    echo "3. Start working on new sessions!"
else
    echo -e "\n${RED}✗ Merge conflicts detected${NC}"
    echo -e "${YELLOW}Don't worry! This is normal when updates overlap with your work.${NC}\n"
    echo "To resolve:"
    echo "1. Open conflicted files (marked with <<<<<<<)"
    echo "2. Keep your work and add new content"
    echo "3. Remove conflict markers"
    echo "4. Run: git add <resolved-files>"
    echo "5. Run: git commit"
    echo ""
    echo "Need help? Check docs/git_workflow.md or ask in class!"
    exit 1
fi
