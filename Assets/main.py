#NOTE THAT YOU SHOULD PASS PATH NAME RELATIVE TO 
#WHERE THIS FILE IS LOCATED

import sys

def pair_combos(c1):
    suitcombos = set()
    my_set = set()
    suits = ['h', 'd', 's', 'c']
    for i in suits:
        for x in suits:
            if i!=x and (i+x) not in suitcombos:
                my_set.add(c1 + i + " " + c1 + x)
                suitcombos.add(i+x)
                suitcombos.add(x+i)
    return my_set

def off_combos(c1,c2):
    myset = set()
    suits = ['h', 'd', 's', 'c']
    for i in suits:
        for x in suits:
            if i!=x:
                myset.add(c1 + i + " " + c2 + x)
    return myset

def suited_combos(c1,c2):
    myset = set()
    suits = ['h', 'd', 's', 'c']
    for i in suits:
        for x in suits:
            if i == x:
                myset.add(c1 + i + " " + c2 + x)
    return myset



def get_combos(c1, c2, s):
    if c1 == c2:
        return pair_combos(c1)
    elif s == 'o':
        return off_combos(c1,c2)
    else:
        return suited_combos(c1,c2)


def main(file_name, data):
    ranges = set()
    face_cards = {'a':'14', 'k':'13', 'q':'12', 'j':'11', 't':'10'}
    

    card1=data[0].lower() 
    card2 = data[1].lower()
    suit = data[2].lower()
    #card1 = card1.lower()
    #card2 = card2.lower()
    if card1 in face_cards.keys():
        card1 = face_cards[card1]
    if card2 in face_cards.keys():
        card2 = face_cards[card2]
    
    temp = get_combos(card1, card2, suit)
    for i in temp:
        ranges.add(i)

    with open(file_name, 'a') as file:
        for i in ranges:
            #print(i)
            file.write(i)
            file.write('\n')





if __name__ == '__main__':
    assert len(sys.argv) > 1, "Error need to enter dir and file name"
    dir = sys.argv[1]
    file_name = dir + "/ranges.txt"
    cards = []
    with open('ranges.txt', 'r') as f:
        for i in f:
            cards.append(i)
    for i in cards:
        data = []
        word = ""
        for x in i:
            if x!= " ":
                word += x 
            else:
                data.append(word)
                word = ""
        data.append(word) 
        main(file_name, data)
