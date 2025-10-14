# Reliable Rhinos File Editing Software
A comprehensive C-based file management system that provides robust file editing capabilities with complete change tracking.


## Features
### File Operations
1. Create new files with multi-line content
2. Copy files to new locations
3. Delete files securely
4. Rename existing files
5. Display complete file contents


### Line Editing
1. Append new lines to files
2. Insert lines at specific positions
3. Delete specific lines
4. Edit existing lines
5. View individual lines
6. Count total lines in files

### Change Tracking
1. Comprehensive change log with timestamps
2. Operation tracking (create, copy, delete, edit, etc.)
3. Line count monitoring
4. Circular buffer for efficient log management


## Menu Options
| Option | Function | Description |
|--------|----------|-------------|
| 1 | Create File | Create new file with content input |
| 2 | Copy File | Duplicate file to new location |
| 3 | Delete File | Remove file permanently |
| 4 | Show File | Display entire file content |
| 5 | Rename File | Change filename |
| 6 | Append Line | Add line to end of file |
| 7 | Delete Line | Remove specific line |
| 8 | Insert Line | Insert line at position |
| 9 | Show Line | Display specific line |
| 10 | Edit Line | Modify existing line content |
| 11 | Show Change Log | View operation history |
| 12 | Show Number of Lines | Count lines in file |
| 13 | Exit | Close application |


## Project Structure
### Core Components
**Main Program Loop** - Handles user input and menu navigation
**File Operations Module** - Manages file creation, copying, deletion
**Line Editing Module** - Handles line-level manipulations
**Change Log System** - Tracks all operations with timestamps

### Key Functions
`createFile()` - File creation with multi-line input
`copyFile()` - File duplication
`deleteFile()` - Secure file removal
`appendLine()`/`insertLine()`/`deleteLine()`/`editLine()` - Line editing suite
`addToLog()` - Change tracking with timestamps
`countLines()` - Accurate line counting


## Technical Details
### Constants
`MAX_FILENAME = 100` - Maximum filename length
`MAX_CONTENT = 1000` - Maximum file content buffer
`MAX_LINE = 1000` - Maximum line length
`MAX_LOG = 1000` - Maximum change log entries

### Global Variables
`changeLog[MAX_LOG][256]` - Circular buffer for operation logs
`logIndex` - Current position in change log

### Input Handling
1. Uses `fgets()` for safe input reading
2. Proper newline character removal
3. Input validation and error handling
