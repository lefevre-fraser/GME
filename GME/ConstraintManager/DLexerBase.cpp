/* DLGLexerBase.c
 *
 * SOFTWARE RIGHTS
 *
 * We reserve no LEGAL rights to the Purdue Compiler Construction Tool
 * Set (PCCTS) -- PCCTS is in the public domain.  An individual or
 * company may do whatever they wish with source code distributed with
 * PCCTS or the code generated by PCCTS, including the incorporation of
 * PCCTS, or its output, into commerical software.
 *
 * We encourage users to develop software with PCCTS.  However, we do ask
 * that credit is given to us for developing PCCTS.  By "credit",
 * we mean that if you incorporate our source code into one of your
 * programs (commercial product, research project, or otherwise) that you
 * acknowledge this fact somewhere in the documentation, research report,
 * etc...  If you like PCCTS and have developed a nice tool with the
 * output, please mention that you developed it using PCCTS.  In
 * addition, we ask that this header remain intact in our source code.
 * As long as these guidelines are kept, we expect to continue enhancing
 * this system and expect to make other tools available as they are
 * completed.
 *
 * ANTLR 1.33
 * Terence Parr
 * Parr Research Corporation
 * with Purdue University and AHPCRC, University of Minnesota
 * 1989-1998
 */
#include "forcelib.h"
#include <stdio.h>
#include <stdlib.h>

/* I have to put this here due to C++ limitation
 * that you can't have a 'forward' decl for enums.
 * I hate C++!!!!!!!!!!!!!!!
 */

// MR1
// MR1  10-Apr-97  133MR1  Prevent use of varying sizes for the
// MR1  			ANTLRTokenType enum
// MR1

enum ANTLRTokenType { TER_HATES_CPP=0, ITS_UTTER_GARBAGE,		// MR1
					 WITH_SOME_GOOD_IDEAS=9999};	// MR1

#define ANTLR_SUPPORT_CODE

#include "config.h"
#include DLEXERBASE_H

DLGLexerBase::
DLGLexerBase(DLGInputStream *in,
	     unsigned bufsize,
	     int _interactive,
	     int _track_columns)
{
	this->_bufsize = bufsize;
	this->_lextext = new DLGChar[_bufsize];
	if ( this->_lextext==NULL ) {
	    panic("text buffer is NULL");
	}
	this->_begexpr = this->_endexpr = NULL;
	this->ch = this->bufovf = 0;
	this->nextpos = NULL;
	this->cl = 0;
	this->add_erase = 0;
	this->input = in;
	this->_begcol = 0;
	this->_endcol = 0;
	this->_line = 1;
	this->charfull = 0;
	this->automaton = 0;
	this->token_to_fill = NULL;
	this->interactive = _interactive;
	this->track_columns = _track_columns;
	this->debugLexerFlag = 0;					// MR1
	this->parser = NULL;						// MR1
    this->lexErrCount=0;                        // MR11
}

void DLGLexerBase::
setInputStream( DLGInputStream *in )
{
	this->input = in;
	_line = 1;
	charfull = 0;
}

/* saves dlg state, but not what feeds dlg (such as file position) */
void DLGLexerBase::
saveState(DLGState *state)
{
	state->input = input;
	state->interactive = interactive;
	state->track_columns = track_columns;
	state->auto_num = automaton;
	state->add_erase = add_erase;
	state->lookc = ch;
	state->char_full = charfull;
	state->begcol = _begcol;
	state->endcol = _endcol;
	state->line = _line;
	state->lextext = _lextext;
	state->begexpr = _begexpr;
	state->endexpr = _endexpr;
	state->bufsize = _bufsize;
	state->bufovf = bufovf;
	state->nextpos = nextpos;
	state->class_num = cl;
	state->debugLexerFlag = debugLexerFlag;				// MR1
	state->parser = parser;						// MR1
}

void DLGLexerBase::
restoreState(DLGState *state)
{
	input = state->input;
	interactive = state->interactive;
	track_columns = state->track_columns;
	automaton = state->auto_num;
	add_erase = state->add_erase;
	ch = state->lookc;
	charfull = state->char_full;
	_begcol = state->begcol;
	_endcol = state->endcol;
	_line = state->line;
	_lextext = state->lextext;
	_begexpr = state->begexpr;
	_endexpr = state->endexpr;
	_bufsize = state->bufsize;
	bufovf = state->bufovf;
	nextpos = state->nextpos;
	cl = state->class_num;
	debugLexerFlag = state->debugLexerFlag;				// MR1
	parser = state->parser;						// MR1
}

/* erase what is currently in the buffer, and get a new reg. expr */
void DLGLexerBase::
skip()
{
	add_erase = 1;
}

/* don't erase what is in the lextext buffer, add on to it */
void DLGLexerBase::
more()
{
	add_erase = 2;
}

/* substitute c for the reg. expr last matched and is in the buffer */
void DLGLexerBase::
replchar(DLGChar c)
{
	/* can't allow overwriting null at end of string */
	if (_begexpr < &_lextext[_bufsize-1]){
		*_begexpr = c;
		*(_begexpr+1) = '\0';
	}
	_endexpr = _begexpr;
	nextpos = _begexpr + 1;
}

/* replace the string s for the reg. expr last matched and in the buffer */
void DLGLexerBase::
replstr(register DLGChar *s)
{
	register DLGChar *l= &_lextext[_bufsize -1];

	nextpos = _begexpr;
	if (s){
	 	while ((nextpos <= l) && (*(nextpos++) = *(s++))){
			/* empty */
		}
		/* correct for NULL at end of string */
		nextpos--;
	}
	if ((nextpos <= l) && (*(--s) == 0)){
		bufovf = 0;
	}else{
		bufovf = 1;
	}
	*(nextpos) = '\0';
	_endexpr = nextpos - 1;
}

void DLGLexerBase::
errstd(char *s)
{
        lexErrCount++;                              /* MR11 */
        fprintf(stderr,
                "%s near line %d (text was '%s')\n",
                ((s == NULL) ? "Lexical error" : s),
                _line,_lextext);
}

int DLGLexerBase::
err_in()
{
	fprintf(stderr,"No input stream, function, or string\n");
	/* return eof to get out gracefully */
	return EOF;
}

ANTLRTokenType DLGLexerBase::
erraction()
{
	errstd("invalid token");
	advance();
	skip();
	return (ANTLRTokenType) 0;	// bogus, but satisfies compiler
}

_ANTLRTokenPtr DLGLexerBase::
getToken()
{
	if ( token_to_fill==NULL ) panic("NULL token_to_fill");
	ANTLRTokenType tt = nextTokenType();
	_ANTLRTokenPtr tk = token_to_fill->makeToken(tt, _lextext,_line);
	return tk;
}

void DLGLexerBase::
panic(char *msg)
{
	fprintf(stderr, "DLG panic: %s\n", msg);
//
//  7-Apr-97 133MR1
//
	exit(PCCTS_EXIT_FAILURE);					// MR1
}

ANTLRParser * DLGLexerBase::						// MR1
setParser(ANTLRParser *p) {						// MR1
  ANTLRParser	*oldValue=parser;					// MR1
  parser=p;								// MR1
  return oldValue;							// MR1
}									// MR1
									// MR1
ANTLRParser * DLGLexerBase::						// MR1
getParser() {								// MR1
  return parser;							// MR1
}									// MR1
									// MR1
int DLGLexerBase::							// MR1
debugLexer(int newValue) {						// MR1
  int	oldValue=debugLexerFlag;					// MR1
  debugLexerFlag=newValue;						// MR1
  return oldValue;							// MR1
}									// MR1
