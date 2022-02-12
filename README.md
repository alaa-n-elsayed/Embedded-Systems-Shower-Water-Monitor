# Shower-Water-Monitor

As we know water plays an important role in our life so we will talk about the importance of saving it.

After analyzing the issue, we came across the conclusion that the vast majority of wasting water happens during showering.

Moreover, we found that different shower heads can use anywhere from 9.5 liters (2.5 gallons) per minute to less than 6 liters (1.6 gallons) per minute.

Furthermore, Egypt has a water poverty problem and the person's intake of water is less than the average, so we decided to do our bet by raising awareness about water usage.

So, we intended to design and build a device that would work on different aspects of our daily use of water in the shower. It can display the total volume of water used per shower, the cost of the water, and the flow rate.

Despite the capability of that device, we have provided an additional feature that will alarm the person that he/she has exceeded the average amount of water per shower (55 liters).

Our device depends on the signal that is generated from the Water Flow Meter Sensor (YF-S201). This sensor generates pulses that are directly proportional to the volume of the water.

We receive the pulses from the sensor through our PCB then we transmit these pulses to our AVR Processor which process this signal and produce a number that indicates the total volume of the water. After that we do some mathematical calculation to get the flow rate and cost of water.

In the further step, we need to make these values (volume, flow rate, and cost) visible to the user, therefore we used LCD 2*16 to display the values on it as follows:
**1st mode** It can display the total volume and flow rate
**2nd mode** It displays the total volume and the cost of used water

This project is designed with the concept of the layered architecture to make it portable with any kind of IDE and could be uploaded to other types of microcontrollers with simple edits.


This is a photo of our product after the final finish with the cooperation with the team of mechanical and hardware:


![Final Product](https://user-images.githubusercontent.com/69085240/153477242-40d8fd46-4ee7-405e-8cc6-d600f0c5b327.jpg)
