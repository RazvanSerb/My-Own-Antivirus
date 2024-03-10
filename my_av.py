#!/usr/bin/env python3

fisierin = open("data/urls/urls.in", 'r', encoding="utf8")
fisierout = open("urls-predictions.out", 'w', encoding="utf8")
while 1:
    url = fisierin.readline()
    url = url.strip()
    if url == "":
        break
    punct = url.find(".")
    delimitator = punct+url[punct:].find('/')
    if delimitator != punct-1:
        url_domain = url[:delimitator]
    else:
        url_domain = url
    BEC = 0
    bazadateurl = open("data/urls/domains_database", 'r', encoding="utf8")
    while 1:
        sir = bazadateurl.readline()
        if sir == "":
            break
        sir = sir.strip()
        if url_domain.find(sir) >= 0:
            BEC = 1
            break
    bazadateurl.close()
    if url.find(".exe") >= 0 or url.find(".bin") >= 0:
        BEC = 1
    for i in range(len(url_domain)):
        if ord(url_domain[i]) >= ord('0') and ord(url_domain[i]) <= ord('9'):
            BEC = 1
            break
    fisierout.write(str(BEC))
    fisierout.write('\n')
fisierin.close()
fisierout.close()

fisierin = open("data/traffic/traffic.in", 'r', encoding="utf8")
fisierout = open("traffic-predictions.out", 'w', encoding="utf8")
sir = fisierin.readline()
sir = sir.strip()
lista_sir = sir.split(',')
for poz in range(len(lista_sir)):
    if lista_sir[poz] == "flow_duration":
        poz_fd = poz
    if lista_sir[poz] == "flow_pkts_payload.avg":
        poz_fppa = poz
while 1:
    sir = fisierin.readline()
    sir = sir.strip()
    if sir == "":
        break
    lista_sir = sir.split(',')
    for poz in range(len(lista_sir)):
        if poz == poz_fd:
            flow_duration = lista_sir[poz]
        if poz == poz_fppa:
            flow_pkts_payload_avg = float(lista_sir[poz])
    BEC = 0
    if flow_pkts_payload_avg != float(0):
        if flow_duration[0] != '0':
            BEC = 1
        else:
            if flow_duration[7] != '0' or flow_duration[8] != '0':
                BEC = 1
            else:
                if flow_duration[10] != '0' or flow_duration[11] != '0':
                    BEC = 1
                else:
                    if flow_duration[13] != '0' or flow_duration[14] != '0':
                        BEC = 1
                    if flow_duration[13] == '0' and flow_duration[14] == '1':
                        if flow_duration[15] == '\0':
                            BEC = 0
    fisierout.write(str(BEC))
    fisierout.write('\n')
fisierin.close()
fisierout.close()
