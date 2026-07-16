# BMW E39 Gear Shift Indicator

A custom PCB gear shift indicator for the BMW E39, built from scratch — from a breadboard prototype and Arduino code, through a cardboard fitment mockup, a KiCad schematic/PCB, JLCPCB manufacturing, to a working install in the car.

## Table of Contents
- [1. Breadboard Prototype & Arduino Code](#1-breadboard-prototype--arduino-code)
- [2. Measuring Template with Cardboard](#2-measuring-template-with-cardboard)
- [3. KiCad Schematic & PCB](#3-kicad-schematic--pcb)
- [4. Printing from JLCPCB](#4-printing-from-jlcpcb)
- [5. Testing Assembly in Car](#5-testing-assembly-in-car)
- [6. Final Project Demo](#6-final-project-demo)
- [Credit](#credit)

---

## 1. Breadboard Prototype & Arduino Code

Before designing a PCB, I built the circuit on a breadboard — wiring up the display and hall effect sensors to an Arduino — and wrote and tested the code to make sure the logic and display output worked correctly before committing to a custom board. The display datasheets were extremely helpful for getting the screen working with the Arduino micro controller. 





**Initial screen demo:**
<p align="center">
  <video src="https://github.com/user-attachments/assets/d19b766d-0b28-46d4-b545-26aa207e68b7" controls width="600">
    Your browser does not support the video tag.
  </video>
</p>

<p align="center">
  <video src="https://github.com/user-attachments/assets/6b89061c-957d-4a28-bf3f-c886c59b977f" controls width="600">
    Your browser does not support the video tag.
  </video>
</p>



---

## 2. Measuring Template with Cardboard

Before committing to a PCB outline, I cut a cardboard template to match the exact mounting space in the dash/console, so the final board would drop in without any fitment surprises.

<p align="center">
  <img src="photos/measuring_template.jpg" width="70%" alt="Cardboard measuring template">
</p>

<p align="center">
  <video src="https://raw.githubusercontent.com/ChickenSoda04/BMW-E39-Gear-Shift-Indicator/main/videos/cardboard_template.mp4" controls width="600">
    Your browser does not support the video tag.
  </video>
</p>

---

## 3. KiCad Schematic & PCB

With the form factor confirmed, I designed the schematic and PCB layout in KiCad, matching the board outline to the cardboard template.

**Schematic:**
<p align="center">
  <img src="photos/schematic.png" width="70%" alt="KiCad schematic">
</p>

**PCB Layout (Front / Back):**
<p align="center">
  <img src="photos/kicad_front.png" width="45%" alt="KiCad PCB - front">
  <img src="photos/kicad_back.png" width="45%" alt="KiCad PCB - back">
</p>


**3D render walkthrough:**
<p align="center">
  <video src="https://github.com/user-attachments/assets/9900a72d-7016-4ad4-b393-e1eb116858c7
" controls width="600">
    Your browser does not support the video tag.
  </video>
</p>

All CAD source files (schematic, PCB, project, and Gerbers) are in [`gear_indicator_cad_files/`](gear_indicator_cad_files).

---

## 4. Printing from JLCPCB

Once the design was finalized, the Gerber files were sent to JLCPCB for manufacturing.

<p align="center">
  <img src="photos/final_pcb_image.jpg" width="70%" alt="Final PCB">
</p>

<p align="center">
  <img src="photos/pcb_front.png" width="45%" alt="Printed PCB - front">
  <img src="photos/pcb_back.png" width="45%" alt="Printed PCB - back">
</p>

<p align="center">
  <video src="https://raw.githubusercontent.com/ChickenSoda04/BMW-E39-Gear-Shift-Indicator/main/videos/printed_pcb.mp4" controls width="600">
    Your browser does not support the video tag.
  </video>
</p>

---

## 5. Testing Assembly in Car

With the printed board in hand, next came test-fitting it in the car and validating the hall effect sensors against actual gear shift positions.

<p align="center">
  <img src="photos/before.jpg" width="70%" alt="Before install">
</p>

**Fitment test:**
<p align="center">
  <video src="https://github.com/user-attachments/assets/2465236a-05b8-4c8a-bc68-1f0bb54ee02c" controls width="600">
    Your browser does not support the video tag.
  </video>
</p>

---

## 6. Final Project Demo

The finished gear shift indicator, installed and running in the car.

<p align="center">
  <video src="https://github.com/user-attachments/assets/e65f4005-9a61-41ae-bb93-482aaea8f4e5
" controls width="600">
    Your browser does not support the video tag.
  </video>
</p>





---

## Credit

The round IPS display wiring, driver setup, and screen graphics approach used in this project were based on [upir](https://www.youtube.com/@upir)'s tutorial, [Arduino UNO with Round LCD IPS Display](https://www.youtube.com/watch?v=pbqgrv5YSf0&list=PLYljjO3cgruen1KPtTqZPnxCy7SrkpltR&index=12). Big thanks for the clear breakdown of the display setup and code.

**Display datasheets / reference docs:**
- [MSP0962/MSP0963 Specification (PDF)](https://www.lcdwiki.com/res/MSP0962_MSP0963/MSP0962_MSP0963_Specification_EN_V1.0.pdf)
- [MSP0962/MSP0963 SPI Demo Instructions — UNO/Mega2560 (PDF)](https://www.lcdwiki.com/res/MSP0962_MSP0963/0.96inch_SPI_MSP0962_MSP0963_UNO_Mega2560_Demo_Instructions_EN.pdf)

