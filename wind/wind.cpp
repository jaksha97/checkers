#include <wx/wx.h>
#include <wx/socket.h>
#include <wx/valgen.h>

int e = 15;			//************************
int rad = 12;

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

class DrawPanel;
// Фрайм  который содержит панель, на которой две кнопки,
// и панель для рисования
class AddE: public wxFrame{
 public:
    AddE(const wxString& title);
    wxPanel *m_pan; // панель для кнопок и планшета
    wxButton *bt, *ng; //, *bp; // кнопки смены цвета и закрытия
    DrawPanel *dp;  // панель для рисования
    wxMenuBar *menubar; // полоска для меню
    wxMenu *file; // менюшка  на полоске
    wxStatusBar *sb; // статус бар
    wxString ss;
    
// Функция закрытия окна
    void OnQuit(wxCommandEvent& event);
    void OnNew(wxCommandEvent& event);
// Функция изменения цвета
//    void CangeColor(wxCommandEvent& event);
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


//////////check20///////////////

check20::check20(){
	for(int i = 0; i < 20; i++)
		a[i]=0;
	for(int i = 2; i < 6; i++)
		a[i]=1;
	for(int i = 12; i < 16; i++)
		a[i]=-1;

//	a[0] = 1;
//	a[4] = -1;
	for(int i = 0; i < 8; i++)
		pos[i] = wxPoint(20 + 30 * i,20);
	pos[8] = wxPoint(230,50);
	pos[9] = wxPoint(230,80);
	for(int i = 0; i < 8; i++)
		pos[10 + i] = wxPoint(230 - i * 30,110);
	pos[18] = wxPoint(20,80);
	pos[19] = wxPoint(20,50);
 
	stepClear();
};

int check20::getNum(wxPoint t){
	for(int i = 0; i < 20; i++)
		if(pos[i].x < t.x && t.x < pos[i].x + 2*e
		&& pos[i].y < t.y && t.y < pos[i].y + 2*e)
			return i;
	return -1;
};


void check20::stepClear(){
	for(int i = 0; i < 2; i++){
		next[i].who = -1;
		next[i].green = -1;
		next[i].where = -1;
		next[i].dead = -1;
	}
}

void check20::stepPrep(int i){
	stepClear();
	int next_i, prev_i;	

	if(i == 0)	
		prev_i = 19;
	else 
		prev_i = i - 1;

	if(i == 19)
		next_i = 0;
	else 
		next_i = i + 1;

	if(a[prev_i] == 0){
		next[0].who = i;		
		next[0].green = prev_i;
		next[0].where = prev_i;
	}
	
	if(a[next_i] == 0){
		next[1].who = i;		
		next[1].green = next_i;
		next[1].where = next_i;
	}


	int d_next_i, d_prev_i;	

	if(prev_i == 0)	
		d_prev_i = 19;
	else 
		d_prev_i = prev_i - 1;

	if(next_i == 19)
		d_next_i = 0;
	else 
		d_next_i = next_i + 1;
	
	if(a[d_prev_i] == 0 && a[i] * a[prev_i] == -1){
		next[0].who = i;		
		next[0].green = d_prev_i;
		next[0].where = d_prev_i;
		next[0].dead = prev_i;
	};

	if(a[d_next_i] == 0 && a[i] * a[next_i] == -1){
		next[1].who = i;		
		next[1].green = d_next_i;
		next[1].where = d_next_i;
		next[1].dead = next_i;
	};
		
		 
};

bool check20::ingreen(int i){
	if(next[0].green == i || next[1].green == i)
		return 1;
	else
		return 0;

};

void check20::act(int i){
	if(next[0].green == i){
		a[next[0].where] = a[next[0].who];
		a[next[0].who] = 0;
		if(next[0].dead != -1)
			a[next[0].dead] = 0;
	}
	
	if(next[1].green == i){
		a[next[1].where] = a[next[1].who];
		a[next[1].who] = 0;
//	0	a[next[1].dead] = 0;                     //****************************
		if(next[1].dead != -1)
			a[next[1].dead] = 0;
	}
	
	//m_SocketClient
	stepClear();
};
//asdasd

////////////////////////////
class Pril: public wxApp{
    public:
        virtual bool OnInit();
};
const int ID_DRAW =1001;
const int ID_BUTTON =1002;
//_________________________________________________
AddE::AddE(const wxString &title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,400)){
// создание панельки для кнопок и рисовалки
    m_pan= new wxPanel(this,wxID_ANY);
// прицепили на эту панельку первую кнопку
    bt= new wxButton(m_pan,wxID_EXIT,wxT("QUit"),wxPoint(10,10));
    ng= new wxButton(m_pan,ID_BUTTON,wxT("New"),wxPoint(100,10));
// прицепили вторую кнопку
//    bp= new wxButton(m_pan,ID_BUTTON , wxT("Red"), wxPoint(100, 10));

// прицепили панельку для рисования
    dp=new DrawPanel(m_pan);


// создали полоску для менюшки
    menubar = new wxMenuBar;

// создали менюшку
    file = new wxMenu;
// добавили к менюшке раздел quit
    file->Append(wxID_EXIT, wxT("&Quit"));
    file->Append(ID_BUTTON, wxT("&New"));
// закинули менюшку на полоску
    menubar->Append(file, wxT("&File"));
 // установили полоску в окно
    SetMenuBar(menubar);
// подключили кнопку закрытия к событиям
    Connect(wxID_EXIT,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AddE::OnQuit));
// подключили менюшку
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AddE::OnQuit));

// подключили кнопку смены 
  Connect(ID_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AddE::OnNew));
  Connect(ID_BUTTON, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AddE::OnNew));


// текст вывели
      ss<<wxT("QQQ!");
 // создали статус-бар
     sb=CreateStatusBar();
    sb->SetStatusText(ss);


};

void AddE::OnQuit(wxCommandEvent& event){
  Close(true);
};

void AddE::OnNew(wxCommandEvent& event){
	delete dp;
	dp=new DrawPanel(m_pan);
};
/*
void AddE::CangeColor(wxCommandEvent& event){
  dp->cx+=50;
  ss<<wxT("Push:")<<dp->cx<<' ';
   sb->SetStatusText(ss);
//перерисовка панели
   m_pan->Refresh();

};
*/


DrawPanel::DrawPanel(wxPanel *parent):wxPanel(parent, -1,wxPoint(50,100),wxSize(280,160),wxBORDER_SUNKEN){
	// подключили панель к событиям рисования
	Connect(wxEVT_PAINT,wxPaintEventHandler(DrawPanel::OnPaint));
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(DrawPanel::OnDclick));
	//    par = parent
	int z=0;
	cx=255;
	cy=255;
	cz=255;

	pl = check20();

};

void DrawPanel::OnPaint(wxPaintEvent& event){
	wxPaintDC dc(this);
	dc.SetBrush(wxBrush(wxColour(255,255,255)));
	dc.SetPen(wxPen(wxColour(0,0,0), 1));
	for(int i = 0; i < 20; i++)
		dc.DrawRectangle(pl.pos[i], wxSize(30,30));
	
	dc.SetBrush(wxBrush(wxColour(0,255,0)));
	for(int i = 0; i < 2; i++)
		if(pl.next[i].green != -1)
			dc.DrawRectangle(pl.pos[pl.next[i].green], wxSize(30,30));

	dc.SetBrush(wxBrush(wxColour(255,255,255)));
	for(int i = 0; i < 20; i++)
		if(pl.a[i] == 1){
			dc.SetPen(wxPen(wxColour(0,0,0), 2));
			dc.DrawCircle(pl.pos[i].x + e, pl.pos[i].y + e, rad);
		}
	
	dc.SetBrush(wxBrush(wxColour(100,100,100)));
	for(int i = 0; i < 20; i++)
		if(pl.a[i] == -1){
			dc.SetPen(wxPen(wxColour(0,0,0), 2));
			dc.DrawCircle(pl.pos[i].x + e, pl.pos[i].y + e, rad);
		}
};

void DrawPanel::OnDclick(wxMouseEvent& event){
        
	
	wxClientDC dc(this);
	dc.SetBrush(wxBrush(wxColour(0,255,0)));        
//	if(event.GetPosition()
	int num = pl.getNum(event.GetPosition());
	if(num != -1 && pl.a[num] != 0 && !(pl.ingreen(num)))
		pl.stepPrep(num);
	else if(num != -1 && pl.ingreen(num))
		pl.act(num);
	else 
		pl.stepClear();

	//if(num != -1)
	//	dc.DrawRectangle(pl.pos[num], wxSize(30,30));
//	sleep(1);	
//
	this->Refresh();
};

IMPLEMENT_APP(Pril);

bool Pril::OnInit()
{
  AddE *ae=new AddE(wxT("Странные шашки"));
  ae->Show(true);
  return true;
};
