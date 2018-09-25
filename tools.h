//void printlnf(int x,int y,String text,int color,int sizef=1){
//  int fW=5;
//  int fH=7;
//  tft.fillRect(x,y,sizef*fW*text.length()+sizef*(text.length()-1),sizef*fH,BG);
//  tft.setCursor(x, y);
//  tft.setTextColor(color);
//  tft.setTextSize(sizef);
//  tft.println(text);
//  yield();
//}
//void select(int id=1){
//  tft.setFont(&Supermarketed10pt7b);
//  if(previd==0){
//    tft.fillRect(0,11+(id*22),320,22,ILI9341_WHITE);
//    tft.setCursor(10,id*22+27);
//    tft.setTextColor(tft.color565(0, 191, 255));
//    tft.println(arr[id-1][2]+arr[id-1][3]);
//    previd=id;
//  }else{
//    tft.drawLine(0,previd*22+10,320,previd*22+10,ILI9341_WHITE);
//    tft.fillRect(0,11+(previd*22),320,22,tft.color565(0, 191, 255));
//    tft.setCursor(10,previd*22+27);
//    tft.setTextColor(ILI9341_WHITE);
//    tft.println(arr[previd-1][2]+arr[previd-1][3]);
//    tft.fillRect(0,11+(id*22),320,22,ILI9341_WHITE);
//    tft.setCursor(10,id*22+27);
//    tft.setTextColor(tft.color565(0, 191, 255));
//    tft.println(arr[id-1][2]+arr[previd-1][3]);
//    previd=id;
//  }
//  yield();
//}
