#include "wind.h"

const int e = 15;
const int BLACK = -1;
const int WHITE = 1;
const int FREE = 0;			//************************
const int rad = 12;

//////////check20///////////////
check20::check20(){
	for(int i = 0; i < 20; i++)
		a[i] = FREE;
	for(int i = 2; i < 6; i++)
		a[i] = WHITE;
	for(int i = 12; i < 16; i++)
		a[i] = BLACK;

	for(int i = 0; i < 8; i++)
		pos[i] = wxPoint(20 + 30 * i,20);
	pos[8] = wxPoint(230,50);
	pos[9] = wxPoint(230,80);
	for(int i = 0; i < 8; i++)
		pos[10 + i] = wxPoint(230 - i * 30,110);
	pos[18] = wxPoint(20,80);
	pos[19] = wxPoint(20,50);
 
	turn = WHITE;	

	stepClear();
};

int check20::getNum(wxPoint t){
	for(int i = 0; i < 20; i++)
		if(pos[i].x < t.x && t.x < pos[i].x + 2 * e
		&& pos[i].y < t.y && t.y < pos[i].y + 2 * e)
			return i;
	return -1;
};


void check20::stepClear(){
	for(int i = 0; i < 2; i++){
		go[i].who = -1;
		go[i].green = -1;
		for(int j = 0; j < 4; j++)		
			go[i].dead[j] = -1;
	}
}

void check20::stepPrep(int i){
	stepClear();
	Iter t(a);
	
	int j = i, k = 0;
	while(a[t[j-2]] == FREE && a[t[i]] * a[t[j-1]] == -1){
		go[0].who = i;		
		go[0].green = t[j-2];
		go[0].dead[k] = t[j-1];
		k++;
		j = t[j-2];
	};

	j = i; k = 0;
	while(a[t[j+2]] == FREE && a[t[i]] * a[t[j+1]] == -1){
		go[1].who = i;		
		go[1].green = t[j+2];
		go[1].dead[k] = t[j+1];
		k++;
		j = t[j+2];
	};
	
	
	if(a[t[i-1]] == FREE && go[1].dead[0] == -1){
		go[0].who = i;		
		go[0].green = t[i-1];
	}
	
	if(a[t[i+1]] == FREE && go[0].dead[0] == -1){
		go[1].who = i;		
		go[1].green = t[i+1];
	}

};

bool check20::ingreen(int i){
	if(go[0].green == i || go[1].green == i)
		return 1;
	else
		return 0;

};


void check20::act(int i){
	if(go[0].green == i){
		a[go[0].green] = a[go[0].who];
		a[go[0].who] = 0;
		for(int j = 0; j < 4; j++)
			if(go[0].dead[j] != -1)
				a[go[0].dead[j]] = FREE;
	} else if(go[1].green == i){
		a[go[1].green] = a[go[1].who];
		a[go[1].who] = 0;
		for(int j = 0; j < 4; j++)
			if(go[1].dead[j] != -1)
				a[go[1].dead[j]] = FREE;	
	}


	if(turn == WHITE)
		turn = BLACK;
	else 
		turn = WHITE;	
	

	//m_SocketClient
	stepClear();



};
////////////////////////////

const int ID_DRAW =1001;
const int ID_BUTTON =1002;

//constructor AddE
AddE::AddE(const wxString &title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(500,400)){

	ss<<wxT("QQQ!");
	sb=CreateStatusBar();
	sb->SetStatusText(ss);

	m_pan= new wxPanel(this,wxID_ANY);

	bt= new wxButton(m_pan,wxID_EXIT,wxT("Quit"),wxPoint(10,10));
	ng= new wxButton(m_pan,ID_BUTTON,wxT("New"),wxPoint(100,10));
	dp=new DrawPanel(m_pan, sb);

	menubar = new wxMenuBar;
	file = new wxMenu;
	file->Append(wxID_EXIT, wxT("&Quit"));
	file->Append(ID_BUTTON, wxT("&New"));
	menubar->Append(file, wxT("&File"));
	SetMenuBar(menubar);
	Connect(wxID_EXIT,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(AddE::OnQuit));

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AddE::OnQuit));
	Connect(ID_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AddE::OnNew));
	Connect(ID_BUTTON, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AddE::OnNew));

	
};

void AddE::OnQuit(wxCommandEvent& event){
  Close(true);
};

void AddE::OnNew(wxCommandEvent& event){
	delete dp;
	dp=new DrawPanel(m_pan, sb);
};

DrawPanel::DrawPanel(wxPanel *parent, wxStatusBar *sb):wxPanel(parent, -1,wxPoint(50,100),wxSize(280,160),wxBORDER_SUNKEN){
	// подключили панель к событиям рисования
	Connect(wxEVT_PAINT,wxPaintEventHandler(DrawPanel::OnPaint));
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(DrawPanel::OnDclick));
	
	dpsb = sb;
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
		if(pl.go[i].green != -1)
			dc.DrawRectangle(pl.pos[pl.go[i].green], wxSize(30,30));

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
	wxString ss;

	if(pl.turn == WHITE)
		ss<<wxT("Ход белых..");
	else
		ss<<wxT("Ход чёрных..");

	dpsb->SetStatusText(ss);

};

void DrawPanel::OnDclick(wxMouseEvent& event){      
	wxClientDC dc(this);
	dc.SetBrush(wxBrush(wxColour(0,255,0)));        
//	if(event.GetPosition()
	int num = pl.getNum(event.GetPosition());
	if(num != -1 && pl.a[num] != 0 && pl.a[num] == pl.turn && !(pl.ingreen(num)))
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

///////////////// Iter /////////////////

check20::Iter::Iter(int* a){
	idx = 0;
	arr = a;	
};

check20::Iter* check20::Iter::operator=(int i){
	idx = (i + 20) % 20;
};

check20::Iter* check20::Iter::operator++(int){
	idx = (idx + 1) % 20;
};

int check20::Iter::operator[](int i){		
	return (i + 20) % 20;
};

int check20::Iter::operator*(){
	return arr[idx];
};

////////////////////////////////////////////////

IMPLEMENT_APP(Pril);

bool Pril::OnInit()
{
  AddE *ae=new AddE(wxT("Странные шашки"));
  ae->Show(true);
  return true;
};





