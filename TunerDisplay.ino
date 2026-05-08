void noteDisplayChannel1(int frequency)
{
  int chanShift = -20;
  if ((158<frequency && 161>frequency) || (318<frequency && 323>frequency)  || (636<frequency && 650>frequency)   || (1272<frequency && 1302>frequency)   || (2550<frequency && 2590>frequency)   || (5155<frequency && 5170>frequency)   || (10180<frequency && 10320>frequency) || (20100<frequency && 20200>frequency) )   
      
         {display.setCursor(33 + chanShift, 35); 
         display.print("-") ;
         note_s = "C";
          
         }
      
      
      if ((161<frequency && 165>frequency) || (323<frequency && 330>frequency)  || (650<frequency && 660>frequency)   || (1302<frequency && 1315>frequency)   || (2590<frequency && 2640>frequency)   || (5170<frequency && 5300>frequency)   || (10320<frequency && 10730>frequency)|| (20200<frequency && 20400>frequency)  )    
      
         {display.setCursor(30 + chanShift, 35);  
          note_s = "C";
         }
      
      
      if ((165<frequency && 168>frequency) || (330<frequency && 336>frequency)  || (660<frequency && 674>frequency)   || (1315<frequency && 1350>frequency)   || (2640<frequency && 2690>frequency)   || (5300<frequency && 5400>frequency)   || (10730<frequency && 10800>frequency) || (20400<frequency && 20500>frequency) )    
         {display.setCursor(45 + chanShift, 35);  
         display.print("-");
          note_s = "C";
         }
      
      
      //C#
                           
      
      if ((168<frequency && 171>frequency) || (336<frequency && 345>frequency)  || (674<frequency && 689>frequency)   || (1350<frequency && 1378>frequency)   || (2690<frequency && 2750>frequency)   || (5420<frequency && 5500>frequency) || (10800<frequency && 10900>frequency)  )  
      
      
         {display.setCursor(33 + chanShift, 35);  
         display.print("-");
          note_s = "C#";}
      
      if ((171<frequency && 175>frequency) || (345<frequency && 351>frequency)  || (689<frequency && 698>frequency)   || (1378<frequency && 1392>frequency)   || (2750<frequency && 2800>frequency)   || (5490<frequency && 5591>frequency) || (10900<frequency && 11100>frequency)  )    
      
      
         {display.setCursor(30 + chanShift, 35);  
          note_s = "C#";}
      
      if ((175<frequency && 178>frequency) || (351<frequency && 356>frequency)  || (698<frequency && 714>frequency)   || (1392<frequency && 1429>frequency)   || (2800<frequency && 2855>frequency)   || (5581<frequency && 5700>frequency) || (11100<frequency && 11200>frequency)  )    
          
      
      
         {display.setCursor(52 + chanShift, 35);  
         display.print("-");
          note_s = "C#";}
                       
      //D
                            
      if ((178<frequency && 181>frequency)   || (356<frequency && 364>frequency)  || (714<frequency && 731>frequency)   || (1429<frequency && 1461>frequency)   || (2855<frequency && 2923>frequency)   || (5700<frequency && 5830>frequency) || (11200<frequency && 11700>frequency)    )     
      
      
          {display.setCursor(33 + chanShift, 35);
          display.print("-")  ;
          note_s = "D";}
      
      if ((181<frequency && 185>frequency)   || (364<frequency && 370>frequency)  || (731<frequency && 741>frequency)    || (1461<frequency && 1475>frequency)   || (2923<frequency && 2955>frequency)   || (5820<frequency && 5930>frequency)  || (11700<frequency && 11900>frequency)  )    
      
      
          {display.setCursor(30 + chanShift, 35);  
          note_s = "D";}
      
      if ((185<frequency && 188>frequency)   || (370<frequency && 377>frequency)  || (741<frequency && 756>frequency)   || (1475<frequency && 1512>frequency)   || (2955<frequency && 3020>frequency)   || (5920<frequency && 6080>frequency)  || (11900<frequency && 12000>frequency)   )   
      
      
          {display.setCursor(45 + chanShift, 35);  
          display.print("-");
          note_s = "D";}
      
      //D#                     
      
      if ((188<frequency && 192>frequency)  || (377<frequency && 386>frequency)  || (756<frequency && 776>frequency)    || (1512<frequency && 1548>frequency)   || (3020<frequency && 3090>frequency)   || (6080<frequency && 6190>frequency)   || (12000<frequency && 12200>frequency)   )    
      
      
          {display.setCursor(33 + chanShift, 35);  
          display.print("-");
          note_s = "D#";}
      
      if ((192<frequency && 196>frequency)  || (386<frequency && 392>frequency)  || (776<frequency && 785>frequency)    || (1548<frequency && 1563>frequency)   || (3090<frequency && 3125>frequency)   || (6180<frequency && 300>frequency)   || (12200<frequency && 12600>frequency)   )     
      
      
          {display.setCursor(30 + chanShift, 35);  
          note_s = "D#";}
      
      if ((196<frequency && 201>frequency)  || (392<frequency && 400>frequency)  || (785<frequency && 799>frequency)    || (1563<frequency && 1602>frequency)   || (3125<frequency && 3200>frequency)   || (6290<frequency && 6440>frequency)  || (12600<frequency && 12900>frequency)    )     
      
      
          {display.setCursor(52 + chanShift, 35);  
          display.print("-");
          note_s = "D#";}

      //E
                            
      if ((201<frequency && 203>frequency)  || (400<frequency && 408>frequency)  || (799<frequency && 816>frequency)    || (1602<frequency && 1640>frequency)   || (3200<frequency && 3270>frequency)   || (6440<frequency && 6550>frequency)   || (12900<frequency && 13000>frequency)     )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "E";}
      
      
      if ((203<frequency && 208>frequency)   || (408<frequency && 415>frequency)  || (816<frequency && 829>frequency)    || (1640<frequency && 1656>frequency)   || (3270<frequency && 3330>frequency)   || (6540<frequency && 6660>frequency)    || (13000<frequency && 13400>frequency)    )    
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "E";}
      
      if ((208<frequency && 212>frequency)  || (415<frequency && 423>frequency)  || (829<frequency && 844>frequency)    || (1656<frequency && 1700>frequency)   || (3330<frequency && 3400>frequency)   || (6650<frequency && 6850>frequency)     || (13400<frequency && 13500>frequency)   )     
      
      
           {display.setCursor(45 + chanShift, 35); 
           display.print("-") ;
          note_s = "E";}

      //F0
                             
      if ((212<frequency && 215>frequency)  || (423<frequency && 432>frequency)  || (844<frequency && 866>frequency)    || (1700<frequency && 1738>frequency)   || (3400<frequency && 3475>frequency)   || (6850<frequency && 6930>frequency)   || (13500<frequency && 13800>frequency)     )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "F";}
      
      if ((215<frequency && 220>frequency)  || (432<frequency && 442>frequency)  || (866<frequency && 880>frequency)    || (1738<frequency && 1753>frequency)   || (3475<frequency && 3490>frequency)   || (6920<frequency && 7040>frequency)     || (13800<frequency && 14000>frequency)   )     
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "F";}
      
      if ((220<frequency && 224>frequency)  || (442<frequency && 448>frequency)  || (880<frequency && 900>frequency)    || (1753<frequency && 1800>frequency)   || (3490<frequency && 3600>frequency)   || (7030<frequency && 7180>frequency)    || (14000<frequency && 14300>frequency)    )     
      
      
           {display.setCursor(45 + chanShift, 35);  
           display.print("-");
          note_s = "F";}
          
      //F#0
                            
      if ((224<frequency && 229>frequency)  || (448<frequency && 460>frequency)  || (900<frequency && 918>frequency)    || (1800<frequency && 1842>frequency)   || (3600<frequency && 3680>frequency)   || (7180<frequency && 7340>frequency)  || (14300<frequency && 14700>frequency)  )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "F#";}
      
      if ((229<frequency && 234>frequency)  || (460<frequency && 468>frequency)  || (918<frequency && 932>frequency)    || (1742<frequency && 1858>frequency)   || (3680<frequency && 3730>frequency)   || (7330<frequency && 7460>frequency)  || (14700<frequency && 14900>frequency)  )     
      
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "F#";}
      
      if ((234<frequency && 239>frequency)  || (468<frequency && 476>frequency)  || (932<frequency && 955>frequency)    || (1858<frequency && 1915>frequency)   || (3730<frequency && 3820>frequency)   || (7450<frequency && 7630>frequency)  || (14900<frequency && 15100>frequency)  )     
      
      
           {display.setCursor(52 + chanShift, 35);  
           display.print("-");
          note_s = "F#";}
      
      //G0
                           
      if ((239<frequency && 242>frequency)  || (476<frequency && 487>frequency)  || (955<frequency && 973>frequency)    || (1915<frequency && 1953>frequency)   || (3820<frequency && 3900>frequency)   || (7763<frequency && 7800>frequency) || (15100<frequency && 15600>frequency) )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "G";}
      
      if ((242<frequency && 247>frequency)  || (487<frequency && 494>frequency)  || (973<frequency && 988>frequency)    || (1953<frequency && 1968>frequency)   || (3900<frequency && 3950>frequency)   || (7790<frequency && 7910>frequency) || (15600<frequency && 15800>frequency) )     
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "G";}
      
      if ((247<frequency && 252>frequency)  || (494<frequency && 505>frequency)  || (988<frequency && 1005>frequency)    || (1968<frequency && 2020>frequency)   || (3950<frequency && 4030>frequency)   || (7900<frequency && 8100>frequency) || (15800<frequency && 16000>frequency) )     
      
      
           {display.setCursor(45 + chanShift, 35);  
           display.print("-");
          note_s = "G";}
      
      
      //G#0
                             
      
      if ((252<frequency && 257>frequency)  || (505<frequency && 516>frequency)  || (1005<frequency && 1031>frequency)   || (2020<frequency && 2068>frequency)   || (4030<frequency && 4110>frequency)   || (8100<frequency && 8270>frequency)  || (16000<frequency && 16500>frequency)    )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "G#";}
      
      if ((257<frequency && 261>frequency)  || (516<frequency && 525>frequency)  || (1031<frequency && 1045>frequency)   || (2068<frequency && 2085>frequency)   || (4110<frequency && 4180>frequency)    || (8260<frequency && 8390>frequency)  || (16500<frequency && 16700>frequency)   )     
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "G#";}
      
      if ((261<frequency && 266>frequency)  || (525<frequency && 538>frequency)  || (1045<frequency && 1075>frequency)   || (2085<frequency && 2155>frequency)   || (4180<frequency && 4265>frequency)   || (8380<frequency && 8570>frequency)   || (16700<frequency && 17000>frequency)   )     
      
      
           {display.setCursor(52 + chanShift, 35);  
           display.print("-");
          note_s = "G#";}
  
      
      //A0
      
      
      if ((266<frequency && 273>frequency)  || (538<frequency && 546>frequency)  || (1075<frequency && 1093>frequency)   || (2155<frequency && 2190>frequency)   || (4265<frequency && 4385>frequency)   || (8570<frequency && 8730>frequency)    || (17000<frequency && 17400>frequency)   )    
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "A";}
      
      if ((273<frequency && 277>frequency)  || (546<frequency && 555>frequency)  || (1093<frequency && 1117>frequency)   || (2190<frequency && 2210>frequency)   || (4385<frequency && 4480>frequency)   || (8720<frequency && 8880>frequency)    || (17400<frequency && 17800>frequency)   )    
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "A";}
      
      if ((277<frequency && 283>frequency)  || (555<frequency && 567>frequency)  || (1117<frequency && 1137>frequency)   || (2210<frequency && 2285>frequency)   || (4480<frequency && 4560>frequency)   || (8870<frequency && 9050>frequency)    || (17800<frequency && 18200>frequency)   )    
      
      
           {display.setCursor(45 + chanShift, 35);  
           display.print("-");
          note_s = "A";}
      
  
      //A#0
                           
  
      if ((283<frequency && 288>frequency)  || (567<frequency && 578>frequency)  || (1137<frequency && 1158>frequency)   || (2285<frequency && 2320>frequency)   || (4560<frequency && 4630>frequency)   || (9050<frequency && 9250>frequency)   || (18200<frequency && 19500>frequency)   )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "A#";}
      
      if ((288<frequency && 293>frequency)  || (578<frequency && 587>frequency)  || (1158<frequency && 1172>frequency)   || (2320<frequency && 2342>frequency)   || (4630<frequency && 4705>frequency)   || (9240<frequency && 9410>frequency)   || (19500<frequency && 19900>frequency)   )     
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "A#";}
      
      if ((293<frequency && 300>frequency)  || (585<frequency && 600>frequency)  || (1172<frequency && 1190>frequency)   || (2342<frequency && 2410>frequency)   || (4705<frequency && 4800>frequency)   || (9400<frequency && 9580>frequency)   || (19900<frequency && 20000>frequency)   )    
      
      
           {display.setCursor(52 + chanShift, 35);  
           display.print("-");
          note_s = "A#";}
      
      //B0
      
      
      if ((300<frequency && 306>frequency)   || (600<frequency && 612>frequency)  || (1190<frequency && 1222>frequency)   || (2410<frequency && 2460>frequency)   || (4800<frequency && 4895>frequency)   || (9580<frequency && 9800>frequency)  )    
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "B";}
      
      if ((306<frequency && 312>frequency)   || (612<frequency && 623>frequency)  || (1222<frequency && 1237>frequency)   || (2460<frequency && 2482>frequency)   || (4895<frequency && 4950>frequency)    || (9790<frequency && 9990>frequency)  )   
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "B";}
      
      if ((312<frequency && 318>frequency)   || (623<frequency && 636>frequency)  || (1237<frequency && 1272>frequency)   || (2482<frequency && 2550>frequency)   || (4950<frequency && 5055>frequency)   || (9980<frequency && 10180>frequency)  )    
      
      
           {display.setCursor(45 + chanShift, 15);  
           display.print("-");
          note_s = "B";}
       display.setCursor(40 + chanShift, 35);
       display.print(note_s);
    //TOO HIGH FOR NOW
                         
    /*if (  (10180<frequency && 100000>frequency) )    
    
    
          {(digitalWrite(LED3,LOW )),(digitalWrite(LED4,LOW )), (digitalWrite(LED5,LOW )),
          (digitalWrite(LEDE,LOW)),(digitalWrite(LEDD,LOW)),(digitalWrite(LEDC,LOW)),(digitalWrite(LEDDP,HIGH )),(digitalWrite(LEDB,LOW)),(digitalWrite(LEDA,LOW)),(digitalWrite(LEDF,LOW)),(digitalWrite(LEDG,LOW));}*/
    
    
}

void noteDisplayChannel2(int frequency)
{
  int chanShift = 50;
  if ((158<frequency && 161>frequency) || (318<frequency && 323>frequency)  || (636<frequency && 650>frequency)   || (1272<frequency && 1302>frequency)   || (2550<frequency && 2590>frequency)   || (5155<frequency && 5170>frequency)   || (10180<frequency && 10320>frequency) || (20100<frequency && 20200>frequency) )   
      
         {display.setCursor(33 + chanShift, 35); 
         display.print("-") ;
         note_s = "C";
          
         }
      
      
      if ((161<frequency && 165>frequency) || (323<frequency && 330>frequency)  || (650<frequency && 660>frequency)   || (1302<frequency && 1315>frequency)   || (2590<frequency && 2640>frequency)   || (5170<frequency && 5300>frequency)   || (10320<frequency && 10730>frequency)|| (20200<frequency && 20400>frequency)  )    
      
         {display.setCursor(30 + chanShift, 35);  
          note_s = "C";
         }
      
      
      if ((165<frequency && 168>frequency) || (330<frequency && 336>frequency)  || (660<frequency && 674>frequency)   || (1315<frequency && 1350>frequency)   || (2640<frequency && 2690>frequency)   || (5300<frequency && 5400>frequency)   || (10730<frequency && 10800>frequency) || (20400<frequency && 20500>frequency) )    
         {display.setCursor(45 + chanShift, 35);  
         display.print("-");
          note_s = "C";
         }
      
      
      //C#
                           
      
      if ((168<frequency && 171>frequency) || (336<frequency && 345>frequency)  || (674<frequency && 689>frequency)   || (1350<frequency && 1378>frequency)   || (2690<frequency && 2750>frequency)   || (5420<frequency && 5500>frequency) || (10800<frequency && 10900>frequency)  )  
      
      
         {display.setCursor(33 + chanShift, 35);  
         display.print("-");
          note_s = "C#";}
      
      if ((171<frequency && 175>frequency) || (345<frequency && 351>frequency)  || (689<frequency && 698>frequency)   || (1378<frequency && 1392>frequency)   || (2750<frequency && 2800>frequency)   || (5490<frequency && 5591>frequency) || (10900<frequency && 11100>frequency)  )    
      
      
         {display.setCursor(30 + chanShift, 35);  
          note_s = "C#";}
      
      if ((175<frequency && 178>frequency) || (351<frequency && 356>frequency)  || (698<frequency && 714>frequency)   || (1392<frequency && 1429>frequency)   || (2800<frequency && 2855>frequency)   || (5581<frequency && 5700>frequency) || (11100<frequency && 11200>frequency)  )    
          
      
      
         {display.setCursor(52 + chanShift, 35);  
         display.print("-");
          note_s = "C#";}
                       
      //D
                            
      if ((178<frequency && 181>frequency)   || (356<frequency && 364>frequency)  || (714<frequency && 731>frequency)   || (1429<frequency && 1461>frequency)   || (2855<frequency && 2923>frequency)   || (5700<frequency && 5830>frequency) || (11200<frequency && 11700>frequency)    )     
      
      
          {display.setCursor(33 + chanShift, 35);
          display.print("-")  ;
          note_s = "D";}
      
      if ((181<frequency && 185>frequency)   || (364<frequency && 370>frequency)  || (731<frequency && 741>frequency)    || (1461<frequency && 1475>frequency)   || (2923<frequency && 2955>frequency)   || (5820<frequency && 5930>frequency)  || (11700<frequency && 11900>frequency)  )    
      
      
          {display.setCursor(30 + chanShift, 35);  
          note_s = "D";}
      
      if ((185<frequency && 188>frequency)   || (370<frequency && 377>frequency)  || (741<frequency && 756>frequency)   || (1475<frequency && 1512>frequency)   || (2955<frequency && 3020>frequency)   || (5920<frequency && 6080>frequency)  || (11900<frequency && 12000>frequency)   )   
      
      
          {display.setCursor(45 + chanShift, 35);  
          display.print("-");
          note_s = "D";}
      
      //D#                     
      
      if ((188<frequency && 192>frequency)  || (377<frequency && 386>frequency)  || (756<frequency && 776>frequency)    || (1512<frequency && 1548>frequency)   || (3020<frequency && 3090>frequency)   || (6080<frequency && 6190>frequency)   || (12000<frequency && 12200>frequency)   )    
      
      
          {display.setCursor(33 + chanShift, 35);  
          display.print("-");
          note_s = "D#";}
      
      if ((192<frequency && 196>frequency)  || (386<frequency && 392>frequency)  || (776<frequency && 785>frequency)    || (1548<frequency && 1563>frequency)   || (3090<frequency && 3125>frequency)   || (6180<frequency && 300>frequency)   || (12200<frequency && 12600>frequency)   )     
      
      
          {display.setCursor(30 + chanShift, 35);  
          note_s = "D#";}
      
      if ((196<frequency && 201>frequency)  || (392<frequency && 400>frequency)  || (785<frequency && 799>frequency)    || (1563<frequency && 1602>frequency)   || (3125<frequency && 3200>frequency)   || (6290<frequency && 6440>frequency)  || (12600<frequency && 12900>frequency)    )     
      
      
          {display.setCursor(52 + chanShift, 35);  
          display.print("-");
          note_s = "D#";}

      //E
                            
      if ((201<frequency && 203>frequency)  || (400<frequency && 408>frequency)  || (799<frequency && 816>frequency)    || (1602<frequency && 1640>frequency)   || (3200<frequency && 3270>frequency)   || (6440<frequency && 6550>frequency)   || (12900<frequency && 13000>frequency)     )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "E";}
      
      
      if ((203<frequency && 208>frequency)   || (408<frequency && 415>frequency)  || (816<frequency && 829>frequency)    || (1640<frequency && 1656>frequency)   || (3270<frequency && 3330>frequency)   || (6540<frequency && 6660>frequency)    || (13000<frequency && 13400>frequency)    )    
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "E";}
      
      if ((208<frequency && 212>frequency)  || (415<frequency && 423>frequency)  || (829<frequency && 844>frequency)    || (1656<frequency && 1700>frequency)   || (3330<frequency && 3400>frequency)   || (6650<frequency && 6850>frequency)     || (13400<frequency && 13500>frequency)   )     
      
      
           {display.setCursor(45 + chanShift, 35); 
           display.print("-") ;
          note_s = "E";}

      //F0
                             
      if ((212<frequency && 215>frequency)  || (423<frequency && 432>frequency)  || (844<frequency && 866>frequency)    || (1700<frequency && 1738>frequency)   || (3400<frequency && 3475>frequency)   || (6850<frequency && 6930>frequency)   || (13500<frequency && 13800>frequency)     )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "F";}
      
      if ((215<frequency && 220>frequency)  || (432<frequency && 442>frequency)  || (866<frequency && 880>frequency)    || (1738<frequency && 1753>frequency)   || (3475<frequency && 3490>frequency)   || (6920<frequency && 7040>frequency)     || (13800<frequency && 14000>frequency)   )     
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "F";}
      
      if ((220<frequency && 224>frequency)  || (442<frequency && 448>frequency)  || (880<frequency && 900>frequency)    || (1753<frequency && 1800>frequency)   || (3490<frequency && 3600>frequency)   || (7030<frequency && 7180>frequency)    || (14000<frequency && 14300>frequency)    )     
      
      
           {display.setCursor(45 + chanShift, 35);  
           display.print("-");
          note_s = "F";}
          
      //F#0
                            
      if ((224<frequency && 229>frequency)  || (448<frequency && 460>frequency)  || (900<frequency && 918>frequency)    || (1800<frequency && 1842>frequency)   || (3600<frequency && 3680>frequency)   || (7180<frequency && 7340>frequency)  || (14300<frequency && 14700>frequency)  )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "F#";}
      
      if ((229<frequency && 234>frequency)  || (460<frequency && 468>frequency)  || (918<frequency && 932>frequency)    || (1742<frequency && 1858>frequency)   || (3680<frequency && 3730>frequency)   || (7330<frequency && 7460>frequency)  || (14700<frequency && 14900>frequency)  )     
      
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "F#";}
      
      if ((234<frequency && 239>frequency)  || (468<frequency && 476>frequency)  || (932<frequency && 955>frequency)    || (1858<frequency && 1915>frequency)   || (3730<frequency && 3820>frequency)   || (7450<frequency && 7630>frequency)  || (14900<frequency && 15100>frequency)  )     
      
      
           {display.setCursor(52 + chanShift, 35);  
           display.print("-");
          note_s = "F#";}
      
      //G0
                           
      if ((239<frequency && 242>frequency)  || (476<frequency && 487>frequency)  || (955<frequency && 973>frequency)    || (1915<frequency && 1953>frequency)   || (3820<frequency && 3900>frequency)   || (7763<frequency && 7800>frequency) || (15100<frequency && 15600>frequency) )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "G";}
      
      if ((242<frequency && 247>frequency)  || (487<frequency && 494>frequency)  || (973<frequency && 988>frequency)    || (1953<frequency && 1968>frequency)   || (3900<frequency && 3950>frequency)   || (7790<frequency && 7910>frequency) || (15600<frequency && 15800>frequency) )     
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "G";}
      
      if ((247<frequency && 252>frequency)  || (494<frequency && 505>frequency)  || (988<frequency && 1005>frequency)    || (1968<frequency && 2020>frequency)   || (3950<frequency && 4030>frequency)   || (7900<frequency && 8100>frequency) || (15800<frequency && 16000>frequency) )     
      
      
           {display.setCursor(45 + chanShift, 35);  
           display.print("-");
          note_s = "G";}
      
      
      //G#0
                             
      
      if ((252<frequency && 257>frequency)  || (505<frequency && 516>frequency)  || (1005<frequency && 1031>frequency)   || (2020<frequency && 2068>frequency)   || (4030<frequency && 4110>frequency)   || (8100<frequency && 8270>frequency)  || (16000<frequency && 16500>frequency)    )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "G#";}
      
      if ((257<frequency && 261>frequency)  || (516<frequency && 525>frequency)  || (1031<frequency && 1045>frequency)   || (2068<frequency && 2085>frequency)   || (4110<frequency && 4180>frequency)    || (8260<frequency && 8390>frequency)  || (16500<frequency && 16700>frequency)   )     
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "G#";}
      
      if ((261<frequency && 266>frequency)  || (525<frequency && 538>frequency)  || (1045<frequency && 1075>frequency)   || (2085<frequency && 2155>frequency)   || (4180<frequency && 4265>frequency)   || (8380<frequency && 8570>frequency)   || (16700<frequency && 17000>frequency)   )     
      
      
           {display.setCursor(52 + chanShift, 35);  
           display.print("-");
          note_s = "G#";}
  
      
      //A0
      
      
      if ((266<frequency && 273>frequency)  || (538<frequency && 546>frequency)  || (1075<frequency && 1093>frequency)   || (2155<frequency && 2190>frequency)   || (4265<frequency && 4385>frequency)   || (8570<frequency && 8730>frequency)    || (17000<frequency && 17400>frequency)   )    
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "A";}
      
      if ((273<frequency && 277>frequency)  || (546<frequency && 555>frequency)  || (1093<frequency && 1117>frequency)   || (2190<frequency && 2210>frequency)   || (4385<frequency && 4480>frequency)   || (8720<frequency && 8880>frequency)    || (17400<frequency && 17800>frequency)   )    
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "A";}
      
      if ((277<frequency && 283>frequency)  || (555<frequency && 567>frequency)  || (1117<frequency && 1137>frequency)   || (2210<frequency && 2285>frequency)   || (4480<frequency && 4560>frequency)   || (8870<frequency && 9050>frequency)    || (17800<frequency && 18200>frequency)   )    
      
      
           {display.setCursor(45 + chanShift, 35);  
           display.print("-");
          note_s = "A";}
      
  
      //A#0
                           
  
      if ((283<frequency && 288>frequency)  || (567<frequency && 578>frequency)  || (1137<frequency && 1158>frequency)   || (2285<frequency && 2320>frequency)   || (4560<frequency && 4630>frequency)   || (9050<frequency && 9250>frequency)   || (18200<frequency && 19500>frequency)   )     
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "A#";}
      
      if ((288<frequency && 293>frequency)  || (578<frequency && 587>frequency)  || (1158<frequency && 1172>frequency)   || (2320<frequency && 2342>frequency)   || (4630<frequency && 4705>frequency)   || (9240<frequency && 9410>frequency)   || (19500<frequency && 19900>frequency)   )     
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "A#";}
      
      if ((293<frequency && 300>frequency)  || (585<frequency && 600>frequency)  || (1172<frequency && 1190>frequency)   || (2342<frequency && 2410>frequency)   || (4705<frequency && 4800>frequency)   || (9400<frequency && 9580>frequency)   || (19900<frequency && 20000>frequency)   )    
      
      
           {display.setCursor(52 + chanShift, 35);  
           display.print("-");
          note_s = "A#";}
      
      //B0
      
      
      if ((300<frequency && 306>frequency)   || (600<frequency && 612>frequency)  || (1190<frequency && 1222>frequency)   || (2410<frequency && 2460>frequency)   || (4800<frequency && 4895>frequency)   || (9580<frequency && 9800>frequency)  )    
      
      
           {display.setCursor(33 + chanShift, 35);  
           display.print("-");
          note_s = "B";}
      
      if ((306<frequency && 312>frequency)   || (612<frequency && 623>frequency)  || (1222<frequency && 1237>frequency)   || (2460<frequency && 2482>frequency)   || (4895<frequency && 4950>frequency)    || (9790<frequency && 9990>frequency)  )   
      
      
           {display.setCursor(30 + chanShift, 35);  
          note_s = "B";}
      
      if ((312<frequency && 318>frequency)   || (623<frequency && 636>frequency)  || (1237<frequency && 1272>frequency)   || (2482<frequency && 2550>frequency)   || (4950<frequency && 5055>frequency)   || (9980<frequency && 10180>frequency)  )    
      
      
           {display.setCursor(45 + chanShift, 15);  
           display.print("-");
          note_s = "B";}
       display.setCursor(40 + chanShift, 35);
       display.print(note_s);
    //TOO HIGH FOR NOW
                         
    /*if (  (10180<frequency && 100000>frequency) )    
    
    
          {(digitalWrite(LED3,LOW )),(digitalWrite(LED4,LOW )), (digitalWrite(LED5,LOW )),
          (digitalWrite(LEDE,LOW)),(digitalWrite(LEDD,LOW)),(digitalWrite(LEDC,LOW)),(digitalWrite(LEDDP,HIGH )),(digitalWrite(LEDB,LOW)),(digitalWrite(LEDA,LOW)),(digitalWrite(LEDF,LOW)),(digitalWrite(LEDG,LOW));}*/
    
    
}
