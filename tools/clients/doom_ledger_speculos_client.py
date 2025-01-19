import pygame
import sys
import requests
import time

# Initialize Pygame
pygame.init()

# Set up the display
width, height = 400, 300
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Doom ledger client")

url = 'http://127.0.0.1:5000/apdu'

headers = {
    'accept': 'application/json',
    'Content-Type': 'application/json',
}
  
# Main loop
running = True
CLA = "D0"
INS = "0D"

while running:
    t = time.time()
    apdu = CLA + INS
    P1 = "00"
    P2 = "00"
    LC = "00"
    apdudata = ""
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            break

    keys = pygame.key.get_pressed()
    if keys[pygame.K_q]:
        apdu += ("06")
        apdu+= ("00")
        apdu+= ("00")
    elif keys[pygame.K_RETURN]:
        apdu+= ("07")
        apdu+= ("00")
        apdu+= ("00")
    else:
        P1 = "05"
        LC = 0
        if keys[pygame.K_SPACE]:
            LC +=1
            apdudata += "0F"
        if keys[pygame.K_UP]:
            LC +=1
            apdudata += "05"
        if keys[pygame.K_DOWN]:
            LC +=1
            apdudata += "06"
        if keys[pygame.K_LEFT]:
            LC +=1
            apdudata += "07"
        if keys[pygame.K_RIGHT]:
            apdudata += "08"
            LC +=1

            # INS = t - time.time()

    # Fill the screen with a color
    screen.fill((30, 30, 30))
    pygame.display.flip()

    if len(apdudata) > 1:
        apdu+= (P1)
        apdu+= (P2)
        data={ 'data': f"{(apdu + '0'+ str(LC) + apdudata)}"}
        print(f"data={(apdu + '0'+ str(LC)  + apdudata)}")
        requests.post(url=url,headers=headers,json=data)
    elif len(apdu) > 5:
        data={ 'data': f"{(apdu)}"}
        requests.post(url=url,headers=headers,json=data)

# Clean up
pygame.quit()
sys.exit()
