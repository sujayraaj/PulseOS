SEGMENT .DATA
 CountDown DD 0
 SEGMENT .TEXT
 [GLOBAL TimerIRQ]
 TimerIRQ:
     PUSH EAX
     MOV EAX, CountDown
     OR EAX, EAX ; 
     JZ TimerDone
     DEC CountDown
 TimerDone:
     POP EAX
     IRETD
 [GLOBAL _Sleep]
 _Sleep:
     PUSH EBP
     MOV EBP, ESP
     PUSH EAX
     MOV EAX, [EBP + 8] ; 
     MOV CountDown, EAX
 SleepLoop:
     CLI 
     MOV EAX, CountDown
     OR EAX, EAX
     JZ SleepDone
     STI
     NOP 
     NOP
     NOP
     NOP
     NOP
     NOP
     JMP SleepLoop
 SleepDone:
     STI
     POP EAX
     POP EBP
     RETN 8
