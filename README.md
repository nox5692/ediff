# *ediff*: *E*xtended *diff*

---
### What does *ediff* bring to the table?
- Well known **diff** features,
- PNG image histogram comparison,
- CSS selector filescraping and comparison,
- Recursive directory comparison with recpect to file suffixes:
    - Example:
        ```
        Dir1:
            one.css
            flower.png
        Dir2:
            two.css
            house.png
        ```
    - **ediff** will match file suffixes and match them to their respective comparison methods.

## Install, build and run:

### Prerequisites
Before you begin, ensure you have the following tools installed:

- [g++](https://gcc.gnu.org/) (GNU Compiler Collection)
- [make](https://www.gnu.org/software/make/) (GNU Make)
- [libpng](http://www.libpng.org/pub/png/libpng.html) (PNG reference library)

If these tools are not installed, you can typically install them using your system's package manager.

### Installation
1. Clone the repository:

    ```bash
    git clone https://github.com/nox5692/ediff.git
    ```

2. Navigate to the project directory:

    ```bash
    cd ediff
    ```

### Build
To build the project, run the following command:

    ```bash
    make
    ```

### Run
To run the program, execute the following command:

    ```bash
    ./ediff <args>
    ```

### If you have any suggestions or ideas on how to improve this, let me know!
