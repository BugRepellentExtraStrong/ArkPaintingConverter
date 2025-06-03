# ArkPaintingConverter
A program to convert image files to the pnt file format used by ARK: Survival Evolved and vice versa

<h2>How to compile</h2>

```
git clone https://github.com/BugRepellentExtraStrong/ArkPaintingConverter.git
cd ArkPaintingConverter
mkdir build
cd build
cmake ..
make
```
<h2>Running program</h2>
In the build directory type:

```
./ArkPaintingConverter
```
=======
# ArkPaintingConverter

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build and Development Commands

### Requirements
- Qt5 (Core, Widgets, Gui components)
- CMake 3.16 or higher
- C++17 compatible compiler
- Linux development environment (primary target)

### Compilation Steps

**1. Create build directory and configure:**
```bash
mkdir -p build && cd build
cmake ..
```

**2. Build the project:**
```bash
make -j$(nproc)
```

**3. Run the application:**
```bash
./ArkPaintingConverter
```

### Alternative: One-step build and run
```bash
mkdir -p build && cd build && cmake .. && make -j$(nproc) && ./ArkPaintingConverter
```

### Development Commands
**Clean build:**
```bash
rm -rf build
```

**Install (optional):**
```bash
cd build && make install
```

**Uninstall:**
```bash
cd build && make uninstall
```

### Troubleshooting
- Ensure Qt5 development packages are installed: `qt5-base-dev` or equivalent
- If CMake fails to find Qt5, set `Qt5_DIR` environment variable
- For missing libraries, check that `libqt5widgets5`, `libqt5gui5`, `libqt5core5a` are installed

## Architecture Overview

ArkPaintingConverter is a Qt5-based image conversion tool for ARK: Survival Evolved painting files. The application converts regular images into ARK's .pnt painting format using dithering algorithms.

### Core Components

- **MainWindow** (`mainwindow.cpp/h`): Primary GUI controller handling image loading, conversion, and file operations
- **DitherBase** (`ditherbase.h`): Abstract base class for dithering algorithms with three implementations:
  - Floyd-Steinberg (`floyd_steinberg.cpp/h`)
  - Jarvis-Judice-Ninke (`jarvisjudiceninke.cpp/h`) 
  - Sierra (`sierra.cpp/h`)
- **ColorChooser** (`colorchooser.cpp/h`): Widget for selecting ARK color palette from CSV files
- **DrawingArea** (`drawingarea.cpp/h`): Custom widget for displaying images with zoom controls
- **Matrix** (`matrix.h`): Template class for 2D matrix operations
- **TPainting** (`tpainting.h`): Structure defining ARK painting templates

### Data Flow

1. User loads an image via file dialog
2. Selects ARK painting template from `data/painting.ini` (defines canvas dimensions and ratios)
3. Chooses dithering algorithm
4. Choose color palette from `data/ColorTableEvolved.csv`
5. Conversion process scales image and applies dithering to match ARK's limited color palette
6. Outputs .pnt files with proper ARK binary format including 20-byte headers

### File Formats

- **Input**: PNG/JPG images
- **Output**: .pnt files (ARK's proprietary painting format) and PNG conversion back
- **Configuration**: `painting.ini` contains canvas templates, `ColorTableEvolved.csv` contains ARK color definitions

The application handles large images by splitting them into multiple ARK painting canvases when dimensions exceed template limits.

## How to Use the Application

![Application Interface](ark1.png)

### Basic Workflow

**1. Load an Image:**
- Click "File" → "Open" or use the "..." button next to the file path field
- Select a PNG or JPG image file
- The original image appears in the left panel

**2. Configure Canvas Settings:**
- Select ARK painting template from dropdown (Canvas, Male, WarMap, etc.)
- Each template has predefined dimensions matching ARK's painting items
- Adjust target dimensions in PixelX/PixelY fields if needed
- Check "KeepAspectRatio" to maintain image proportions

**3. Choose Color Palette:**
- Right panel shows ARK's available colors with checkboxes
- Select/deselect colors to customize the palette
- Use "Select All" or "Deselect All" buttons for quick changes
- Default colors loaded from `data/ColorTableEvolved.csv`

**4. Set Dithering Options:**
- Choose dithering algorithm: Floyd-Steinberg, Jarvis-Judice-Ninke, or Sierra
- Adjust dither factor (0.0-1.0) to control color blending intensity
- Higher values create smoother gradients, lower values preserve sharp edges

**5. Convert the Image:**
- Click "ConvertImage" to process the image
- Progress bar shows conversion status
- Converted result appears in the right panel
- Use zoom controls (ViewScale%) to inspect details

**6. Export Results:**
- Click "WriteFile" to save as ARK .pnt format
- Large images automatically split into multiple .pnt files for ARK compatibility
- Files saved with canvas positioning data in filename

### Additional Features

![Tools Menu](ark3.png)

**Tools Menu Options:**
- **Convert ARK .pnt to png**: Batch convert .pnt files back to viewable PNG format
- **Save as png**: Export the converted image as PNG
- **Read Color Table**: Load custom color palettes from CSV files

**View Controls:**
- Zoom controls for both original and converted image panels
- Scroll areas for navigating large images
- Status bar shows conversion progress

### File Formats
- **Input**: PNG, JPG images  
- **Output**: .pnt files (ARK painting format), PNG exports
- **Configuration**: painting.ini (canvas templates), ColorTableEvolved.csv (color definitions)
