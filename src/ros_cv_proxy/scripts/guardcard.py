#!/usr/bin/env python
# -*- coding:UTF-8 -*-

from mqutil import RSMQueue
import json
import time

class CardIO():

    # ------mqueue-------
    qcard = RSMQueue('rfid', '127.0.0.1')

    mqInput = []

    time = time.time()

    current_card = {}
    card_list = []
    card_list_len = 5

    def __init__(self):
        print('CardIO start....')

    def run(self):

        def callback(message, obj):
            try:
                obj.GetCard(message)
                return True
            except Exception as e:
                print("[Exception] CardIO callback()", e)
        try:
            self.mqInput = self.qcard.subscribe(callback, self, 100)
            return True
        except Exception as e:
            print("[Exception] CardIO run()", e)

    def GetCard(self, message):
        self.current_card = json.loads(message)
        print(self.current_card['Pname'])
        self.pushCard(self.current_card)
        self.time = time.time()


    def pushCard(self, card):
        self.card_list.append(dict(ts=time.time(), msg=card))

        if len(self.card_list) > self.card_list_len:
            self.card_list.pop(0)



