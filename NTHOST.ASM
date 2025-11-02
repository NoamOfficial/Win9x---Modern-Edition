Host_memory:
resb 6400
db 00 09
Clear_HM:
mov ES, Seg [host_memory]
MOV DI, 0
LODSB
MOV [0x400], AL
RET
Send_command:
MOV ES, Seg [Host_memory]
MOV DI, 0
STOSB
RET
SET_CCS:
MOV ES, Seg [host_memory]
MOV DI, 0
MOV AL, 40
STOSB
RET
CLEAR_CCS:
MOV CX, 6400
MOV ES Seg [Host_memory]
MOV DI, 0
MOV AL, 00
STOSB
ADD DI, 1
LOOP CLEAR_CCS
RET
