import pygame
import sys
import time
from ledgerblue import comm

# Initialize Pygame
pygame.init()

# Set up the display
width, height = 400, 300
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Doom ledger client")

# Main loop
running = True
CLA = 0xD0
INS = 0x0D

dongle = comm.getDongle(True)

while running:
    t = time.time()
    apdu = [CLA, INS]
    P1 = "00"
    P2 = 0x00
    LC = "00"
    apdudata = bytearray([0])
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            break

    keys = pygame.key.get_pressed()
    if keys[pygame.K_q]:
        P1= "06"
        apdu.append(0X06)
        apdu.append(0X00)
        apdu.append(0X00)
    elif keys[pygame.K_RETURN]:
        apdu.append(0X07)
        apdu.append(0X00)
        apdu.append(0X00)
    else:
        P1 = 0x05
        LC = 0x00
        
        if keys[pygame.K_SPACE]:
            LC += 1
            apdudata += bytearray([0x0F])
        if keys[pygame.K_UP]:
            LC += 1
            apdudata += bytearray([0x05])
        if keys[pygame.K_DOWN]:
            LC += 1
            apdudata += bytearray([0x06])
        if keys[pygame.K_LEFT]:
            LC += 1
            apdudata += bytearray([0x07])
        if keys[pygame.K_RIGHT]:
            LC += 1
            apdudata += bytearray([0x08])

    # Fill the screen with a color
    screen.fill((30, 30, 30))
    pygame.display.flip()

    if len(apdudata) > 1:
        apdudata.pop(0)
        apdu.append(P1)
        apdu.append(P2)
        dongle.exchange(bytearray(apdu) + bytearray([len(apdudata)]) + apdudata,150)
    elif len(apdu) > 2:
        dongle.exchange(bytearray(apdu),150)

# Clean up
pygame.quit()
dongle.close()
sys.exit()
