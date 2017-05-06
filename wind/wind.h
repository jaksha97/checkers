#include <wx/wx.h>
#include <wx/socket.h>
#include <wx/valgen.h>

struct Step{
	public:
	int green;	//**************************
	int who;
	int where;
	int dead;	//***************************
	
};

class check20{
public:
	int a[20];  // указатель на область памяти  для игрового поля
	wxPoint pos[20];
	Step next[2];	
	check20();
	int getNum(wxPoint);
	void stepClear();
	void stepPrep(int);
	bool ingreen(int);
	void act(int);	
};

// Класс, описывающий панель для рисования
class DrawPanel: public wxPanel{
  public:	
// в конструкторе указывается адрес объекта, который ее содержит
        DrawPanel(wxPanel *parent);
 // рисовалка
        void OnPaint(wxPaintEvent & event);
// составляющие цвета
        int cx,cy,cz;
	void OnDclick(wxMouseEvent& event); ///////////////////////////////////////////////
	check20 pl;
};

// Фрайм  который содержит панель, на которой две кнопки,
// и панель для рисования
class AddE: public wxFrame{
 public:
    AddE(const wxString& title);
    wxPanel *m_pan; 		// панель для кнопок и планшета
    wxButton *bt, *ng; 		//, *bp; // кнопки смены цвета и закрытия
    DrawPanel *dp; 		 // панель для рисования
    wxMenuBar *menubar; 	// полоска для меню
    wxMenu *file; 		// менюшка  на полоске
    wxStatusBar *sb;		 // статус бар
    wxString ss;
    
// Функция закрытия окна
    void OnQuit(wxCommandEvent& event);
    void OnNew(wxCommandEvent& event);
// Функция изменения цвета
//    void CangeColor(wxCommandEvent& event);
};

class Pril: public wxApp{
    public:
        virtual bool OnInit();
};

