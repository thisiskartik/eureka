import threading
import asyncio
from bleak import BleakClient
from playsound import playsound

noteState = False


def firstNoteCallback(char, data):
    global noteState
    if data == b'1':
        if not noteState:
            print("Playing Sa")
            threading.Thread(target=playsound, args=('Sa.mp3',), daemon=True).start()
        else:
            print("Playing Ga")
            threading.Thread(target=playsound, args=('Ga.mp3',), daemon=True).start()


def secondNoteCallback(char, data):
    global noteState
    if data == b'1':
        if not noteState:
            print("Playing Re")
            threading.Thread(target=playsound, args=('Re.mp3',), daemon=True).start()
        else:
            print("Playing Dha")
            threading.Thread(target=playsound, args=('Dha.mp3',), daemon=True).start()


def thirdNoteCallback(char, data):
    global noteState
    if data == b'1':
        if not noteState:
            print("Playing Pa")
            threading.Thread(target=playsound, args=('Pa.mp3',), daemon=True).start()
        else:
            print("Playing Ni")
            threading.Thread(target=playsound, args=('Ni.mp3',), daemon=True).start()


def fourthNoteCallback(char, data):
    global noteState
    if data == b'1':
        if not noteState:
            print("Playing Ma")
            threading.Thread(target=playsound, args=('Ma.mp3',), daemon=True).start()
        else:
            print("Playing Saa")
            threading.Thread(target=playsound, args=('Saa.mp3',), daemon=True).start()


def changeNoteCallback(char, data):
    global noteState
    if data == b'1':
        noteState = not noteState


async def main(address):
    async with BleakClient(address) as client:
        await client.pair()
        for s in client.services:
            print(s)
            for c in s.characteristics:
                print(c)
            print("\n")
        await client.start_notify("ff997f01-bf82-11ed-afa1-0242ac120002", firstNoteCallback)
        await client.start_notify("ff997f02-bf82-11ed-afa1-0242ac120002", secondNoteCallback)
        await client.start_notify("ff997f03-bf82-11ed-afa1-0242ac120002", thirdNoteCallback)
        await client.start_notify("ff997f04-bf82-11ed-afa1-0242ac120002", fourthNoteCallback)
        await client.start_notify("ff997f05-bf82-11ed-afa1-0242ac120002", changeNoteCallback)
        await asyncio.sleep(86400)


asyncio.run(main("65:A1:1E:5C:76:23"))
