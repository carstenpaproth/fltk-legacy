// generated by Fast Light User Interface Designer (fluid) version 2.0001

#include "coding_style.h"
static int brace_style;
static int no_space_parens;
static int brace_functions;
static int indent_tabs;
static int tab_size;
static int always_return_parens;
static int indent_code;

static void use_coding_style() {
  gbrace_style = brace_style;
gno_space_parens = no_space_parens;
gbrace_functions = brace_functions;
gindent_tabs = indent_tabs;
gtab_size = tab_size;
galways_return_parens = always_return_parens;
}

static Fl_Round_Button *pStyle1=(Fl_Round_Button *)0;

static void cb_pStyle1(Fl_Round_Button* o, void*) {
  if(o->value())
   brace_style = 1;
}

static Fl_Round_Button *pStyle2=(Fl_Round_Button *)0;

static void cb_pStyle2(Fl_Round_Button* o, void*) {
  if(o->value())
   brace_style = 2;
}

static Fl_Round_Button *pStyle3=(Fl_Round_Button *)0;

static void cb_pStyle3(Fl_Round_Button* o, void*) {
  if(o->value())
   brace_style = 3;
}

static Fl_Check_Button *pNoSpaceParens=(Fl_Check_Button *)0;

static void cb_pNoSpaceParens(Fl_Check_Button* o, void*) {
  no_space_parens = o->value();;
}

static Fl_Check_Button *pBraceFuncs=(Fl_Check_Button *)0;

static void cb_pBraceFuncs(Fl_Check_Button* o, void*) {
  brace_functions = o->value();
}

static Fl_Value_Input *pTabSize=(Fl_Value_Input *)0;

static void cb_pTabSize(Fl_Value_Input* o, void*) {
  tab_size = (int)o->value();
}

static Fl_Check_Button *pIndentTabs=(Fl_Check_Button *)0;

static void cb_pIndentTabs(Fl_Check_Button* o, void*) {
  indent_tabs = o->value();
if(o->value())
    pTabSize->hide();
else
   pTabSize->show();
}

static Fl_Check_Button *pIndentCode=(Fl_Check_Button *)0;

static void cb_pIndentCode(Fl_Check_Button* o, void*) {
  indent_code = o->value();
}

static Fl_Check_Button *pReturnParens=(Fl_Check_Button *)0;

static void cb_pReturnParens(Fl_Check_Button* o, void*) {
  always_return_parens = o->value();
}

static void cb_Cancel(Fl_Button* o, void*) {
  o->window()->hide();
}

static void cb_Save(Fl_Button* o, void*) {
  use_coding_style();
save_coding_style();
o->window()->hide();
}

static void cb_Use(Fl_Button* o, void*) {
  use_coding_style();
o->window()->hide();
}

Fl_Window* make_codingstyle_window() {
  Fl_Window* w;
  { Fl_Window* o = new Fl_Window(7, 78, 310, 255);
    w = o;
    { Fl_Tabs* o = new Fl_Tabs(0, 0, 303, 218);
      o->box(FL_EMBOSSED_BOX);
      { Fl_Group* o = new Fl_Group(0, 25, 303, 193, "Brace Style");
        { Fl_Group* o = new Fl_Group(14, 22, 282, 122, "Brace Style");
          o->box(FL_ENGRAVED_BOX);
          o->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
          { Fl_Box* o = new Fl_Box(20, 6, 47, 20, "if ( x ) {");
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
          { Fl_Box* o = new Fl_Box(20, 25, 45, 20, "++y;");
            o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
          }
          { Fl_Box* o = new Fl_Box(20, 41, 36, 20, "}");
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
          { Fl_Box* o = new Fl_Box(114, 6, 47, 20, "if ( x )");
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
          { Fl_Box* o = new Fl_Box(114, 25, 36, 20, "{");
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
          { Fl_Box* o = new Fl_Box(115, 42, 46, 20, "++y;");
            o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
          }
          { Fl_Box* o = new Fl_Box(114, 59, 36, 20, "}");
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
          { Fl_Round_Button* o = pStyle1 = new Fl_Round_Button(16, 84, 66, 25, "Style 1");
            o->type(102);
            o->value(1);
            o->callback((Fl_Callback*)cb_pStyle1);
          }
          { Fl_Box* o = new Fl_Box(201, 6, 47, 20, "if ( x )");
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
          { Fl_Box* o = new Fl_Box(201, 25, 36, 20, "{");
            o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
          }
          { Fl_Box* o = new Fl_Box(227, 42, 34, 22, "++y;");
            o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
          }
          { Fl_Box* o = new Fl_Box(201, 59, 36, 20, "}");
            o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
          }
          { Fl_Round_Button* o = pStyle2 = new Fl_Round_Button(109, 84, 66, 25, "Style 2");
            o->type(102);
            o->callback((Fl_Callback*)cb_pStyle2);
          }
          { Fl_Round_Button* o = pStyle3 = new Fl_Round_Button(200, 84, 66, 25, "Style 3");
            o->type(102);
            o->callback((Fl_Callback*)cb_pStyle3);
          }
          o->end();
        }
        { Fl_Check_Button* o = pNoSpaceParens = new Fl_Check_Button(14, 147, 193, 25, "No space before parentheses");
          o->callback((Fl_Callback*)cb_pNoSpaceParens);
        }
        { Fl_Check_Button* o = pBraceFuncs = new Fl_Check_Button(14, 168, 175, 25, "Apply to function braces");
          o->value(1);
          o->callback((Fl_Callback*)cb_pBraceFuncs);
        }
        o->end();
      }
      { Fl_Group* o = new Fl_Group(0, 25, 303, 183, "Other");
        o->hide();
        { Fl_Group* o = new Fl_Group(11, 22, 218, 90, "Indentation");
          o->box(FL_ENGRAVED_BOX);
          o->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
          { Fl_Value_Input* o = pTabSize = new Fl_Value_Input(129, 33, 31, 25, "Tab size for indents");
            o->maximum(12);
            o->value(2);
            o->callback((Fl_Callback*)cb_pTabSize);
          }
          { Fl_Check_Button* o = pIndentTabs = new Fl_Check_Button(13, 7, 114, 25, "Indent with tabs");
            o->callback((Fl_Callback*)cb_pIndentTabs);
          }
          { Fl_Check_Button* o = pIndentCode = new Fl_Check_Button(14, 58, 151, 25, "Indent code blocks");
            o->callback((Fl_Callback*)cb_pIndentCode);
          }
          o->end();
        }
        { Fl_Check_Button* o = pReturnParens = new Fl_Check_Button(9, 120, 221, 25, "Always use parentheses on return");
          o->callback((Fl_Callback*)cb_pReturnParens);
        }
        o->end();
      }
      o->end();
    }
    { Fl_Button* o = new Fl_Button(106, 223, 59, 25, "Cancel");
      o->callback((Fl_Callback*)cb_Cancel);
    }
    { Fl_Button* o = new Fl_Button(171, 223, 59, 25, "Save");
      o->callback((Fl_Callback*)cb_Save);
    }
    { Fl_Button* o = new Fl_Button(236, 223, 59, 25, "Use");
      o->callback((Fl_Callback*)cb_Use);
    }
    o->end();
  }
  return w;
}

void load_codingstyle_window() {
  brace_style = gbrace_style;
no_space_parens = gno_space_parens;
brace_functions = gbrace_functions;  
indent_tabs = gindent_tabs;
tab_size = gtab_size;
always_return_parens = galways_return_parens;
indent_code = gindent_code;
pStyle1->value(gbrace_style == 1);
pStyle2->value(gbrace_style == 2);
pStyle3->value(gbrace_style == 3);
pNoSpaceParens->value(gno_space_parens);
pBraceFuncs->value(gbrace_functions);
pIndentTabs->value(gindent_tabs);
pTabSize->value(gtab_size);
pReturnParens->value(galways_return_parens);
if(gindent_tabs)
   pTabSize->hide();
else
   pTabSize->show();
pIndentCode->value(gindent_code);
}
