<!-- PROJECT LOGO -->
[![LinkedIn][linkedin-shield]][linkedin-url]
<br />
<p align="center">
  <a href="https://github.com/ProgrammingLuis/Kernel-Mode-Driver">
    <img src="logo/logo.jpeg" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Kernel Mode Driver (Windows 10)</h3>

  <p align="center">
    <br />
    A software driver that is capable of reading and writing from physical memory to virtual. 
    <br />
    <br />
    ·
    <a href="https://github.com/ProgrammingLuis/Kernel-Mode-Driver/issues">Report Bug</a>
    ·
    <a href="https://github.com/ProgrammingLuis/Kernel-Mode-Driver/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Roadmap](#roadmap)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)



<!-- ABOUT THE PROJECT -->
## About The Project

I have always wondered how emulators worked and making my own is my way of learning about them. 

Things I have learned about while working on this project:
* Kernel-mode vs User-mode.
* Operating Systems (Windows 10)
* How memory works
* How to debug drivers

I hope to develop more software drivers in the future. Currently, I am getting some BSODS, but I will fix them. Please let me know about any bugs/issues so that I can get better at this.

A list of commonly used resources that I found helpful are listed in the acknowledgements.

### Built With
This was all done in Community Visual Studio 2019. 
* C
* WDF (Windows Driver Frameworks)

<!-- GETTING STARTED -->
## Getting Started

For now, the driver finds a process and gets a handle to it.

### Prerequisites

To run this program you will need to compile the files in Visual Studio.
* Visual Studio

### Installation
```sh
Visual C
* To build this project in Visual C you will need the Windows Drivers extension, after that download structs.h and Driver.c, then build and run the program.
* To run the program you will have to launch the driver with Driver Signature Enforcement disabled.
```

<!-- USAGE EXAMPLES -->
## Usage

When finished, the program will be able to read and write virtual memory to a desired process.

<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/ProgrammingLuis/Intel8080/issues) for a list of proposed features (and known issues).

<!-- LICENSE -->
## License

Distributed under the GNU License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact

Luis Hernandez - hluis@umich.edu

Project Link: [https://https://github.com/ProgrammingLuis/Intel8080](https://https://github.com/ProgrammingLuis/Intel8080)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [Microsoft Tutorials](https://docs.microsoft.com/en-us/windows-hardware/drivers/gettingstarted/writing-a-very-small-kmdf--driver)
* [Zer0Mem0ry's Driver](https://github.com/Zer0Mem0ry/KernelBhop/tree/master/Driver)
* [Toby Opferman's Tutorials](https://www.codeproject.com/Articles/9504/Driver-Development-Part-1-Introduction-to-Drivers)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/programmingluis/
