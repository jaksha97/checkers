//Пример использования класса

#include "image.h"

int main(){
// Image im(200,200,wxColor(255,255,0));
// Загрузка обработчика изображений
 wxInitAllImageHandlers();
// стандартный объект класса string для имени файла
  string file("file.png");
// создание изображения из файла
 Image im(file);
// файл для новой картинки
 string s = "f1.png";
// цветт заливки
 im.setFill(wxColor(255,255,0));
// цвет линий
 im.setPen(wxColor(255,255,255));
// рисование линий
 im.DrawLine(wxPoint(20,20),wxPoint(60,20));
 im.DrawLine(wxPoint(20,20),wxPoint(20,60));
 im.DrawLine(wxPoint(20,60),wxPoint(60,60));
 im.DrawLine(wxPoint(60,20),wxPoint(60,60));
// закраска прямоугольника, если точка внутри.
// снаружи красить не умеет
 im.FillRec(wxPoint(30,30), wxColor(255,0,0));
// закраска одной точки
 im.ColorPoint(wxPoint(40,40),wxColor(0,255,0));

// "косая" линия
 im.DrawLine(wxPoint(20,20),wxPoint(30,60));
// обращене к точке. получение красной составляющей цвета
 cout<<(int)im.GetRed(25,25)<<endl;
// сохранить в файл
 im.saveToFile(s); 
}
