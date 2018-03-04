# Planificator-de-procese

În proiect am considerat următoarele stări ale unui proces: new, ready, running, waiting și terminated. Există urmatoarele tipul de 
planificări. First Come First Served (1) în cadrul căruia procesele vor pleca în running în ordinea în care au sosit în ready. Ele vor sta
în running până când se termină execuția lor, moment în care vor pleca în starea terminated. Shortest Job First (2) pentru care este 
necesar să știm durata exacta necesară pentru un process să se finalizeze. Atunci când un process trebuie să treacă din ready în running, 
se va allege acel process care va dura cel mai puțin să se termine. Round Robin (3) este asemănător cu FCFS, doar că este preemptive, un 
process poate fi întrerupt din starea running si trimis înapoi în starea ready. Planificarea cu priorități (4) atribuie fiecărui proces un 
nivel de prioritate. Procesele vor intra în starea running în ordinea descrescătoare a nivelelor. Planificarea Bonus(5) ne oferă 
posibilitatea de a modifica prioritatea în funcție de comportamentul procesului. Fișierul de intrare ne indică ce planificare să folosim 
după care există următoarele comenzi. t – tick care trece un timp de ceas. a nume x y – add, vine un nou process din new, 
unde nume = nume_proces, x = timpul necesar pentru rulare și y = prioritate. ma nume1 x1 y1 nume2 x2 y2 … - multiple add. w – wait, 
procesul din running trece în waiting. e nume -  event, un event trezește procesul nume din waiting. s – show, afișează informații despre 
procesul din running.
