/*************************************************************************/
/*  gdscript_tokenizer.h                                                 */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      http://Valjang.fr                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Valjang.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef GDSCRIPT_TOKENIZER_H
#define GDSCRIPT_TOKENIZER_H

#include "core/list.h"
#include "core/set.h"
#include "core/variant.h"
#include "core/vector.h"

class GDScriptTokenizer {
public:
	enum CursorPlace {
		CURSOR_NONE,
		CURSOR_BEGINNING,
		CURSOR_MIDDLE,
		CURSOR_END,
	};

	struct Token {
		enum Type {
			EMPTY,
			// Basic
			ANNOTATION,
			IDENTIFIER,
			LITERAL,
			// Comparison
			LESS,
			LESS_EQUAL,
			GREATER,
			GREATER_EQUAL,
			EQUAL_EQUAL,
			BANG_EQUAL,
			// Logical
			AND,
			OR,
			NOT,
			AMPERSAND_AMPERSAND,
			PIPE_PIPE,
			BANG,
			// Bitwise
			AMPERSAND,
			PIPE,
			TILDE,
			CARET,
			LESS_LESS,
			GREATER_GREATER,
			// Math
			PLUS,
			MINUS,
			STAR,
			SLASH,
			PERCENT,
			// Assignment
			EQUAL,
			PLUS_EQUAL,
			MINUS_EQUAL,
			STAR_EQUAL,
			SLASH_EQUAL,
			PERCENT_EQUAL,
			LESS_LESS_EQUAL,
			GREATER_GREATER_EQUAL,
			AMPERSAND_EQUAL,
			PIPE_EQUAL,
			CARET_EQUAL,
			// Control flow
			IF,
			ELIF,
			ELSE,
			FOR,
			WHILE,
			BREAK,
			CONTINUE,
			PASS,
			RETURN,
			MATCH,
			// Keywords
			AS,
			ASSERT,
			AWAIT,
			BREAKPOINT,
			CLASS,
			CLASS_NAME,
			CONST,
			ENUM,
			EXTENDS,
			FUNC,
			IN,
			IS,
			NAMESPACE,
			PRELOAD,
			SELF,
			SIGNAL,
			STATIC,
			SUPER,
			TRAIT,
			VAR,
			VOID,
			YIELD,
			// Punctuation
			BRACKET_OPEN,
			BRACKET_CLOSE,
			BRACE_OPEN,
			BRACE_CLOSE,
			PARENTHESIS_OPEN,
			PARENTHESIS_CLOSE,
			COMMA,
			SEMICOLON,
			PERIOD,
			PERIOD_PERIOD,
			COLON,
			DOLLAR,
			FORWARD_ARROW,
			UNDERSCORE,
			// Whitespace
			NEWLINE,
			INDENT,
			DEDENT,
			// Constants
			CONST_PI,
			CONST_TAU,
			CONST_INF,
			CONST_NAN,
			// Error message improvement
			VCS_CONFLICT_MARKER,
			BACKTICK,
			QUESTION_MARK,
			// Special
			ERROR,
			TK_EOF, // "EOF" is reserved
			TK_MAX
		};

		Type type = EMPTY;
		Variant literal;
		int start_line = 0, end_line = 0, start_column = 0, end_column = 0;
		int leftmost_column = 0, rightmost_column = 0; // Column span for multiline tokens.
		int cursor_position = -1;
		CursorPlace cursor_place = CURSOR_NONE;
		String source;

		const char *get_name() const;
		// TODO: Allow some keywords as identifiers?
		bool is_identifier() const { return type == IDENTIFIER; }
		StringName get_identifier() const { return literal; }

		Token(Type p_type) {
			type = p_type;
		}

		Token() {
			type = EMPTY;
		}
	};

private:
	String source;
	const CharType *_source = nullptr;
	const CharType *_current = nullptr;
	int line = -1, column = -1;
	int cursor_line = -1, cursor_column = -1;
	int tab_size = 4;

	// Keep track of multichar tokens.
	const CharType *_start = nullptr;
	int start_line = 0, start_column = 0;
	int leftmost_column = 0, rightmost_column = 0;

	// Info cache.
	bool line_continuation = false; // Whether this line is a continuation of the previous, like when using '\'.
	bool multiline_mode = false;
	List<Token> error_stack;
	bool pending_newline = false;
	Token last_newline;
	int pending_indents = 0;
	List<int> indent_stack;
	List<CharType> paren_stack;
	CharType indent_char = '\0';
	int position = 0;
	int length = 0;

	_FORCE_INLINE_ bool _is_at_end() { return position >= length; }
	_FORCE_INLINE_ CharType _peek(int p_offset = 0) { return position + p_offset >= 0 && position + p_offset < length ? _current[p_offset] : '\0'; }
	int indent_level() const { return indent_stack.size(); }
	bool has_error() const { return !error_stack.empty(); }
	Token pop_error();
	CharType _advance();
	void _skip_whitespace();
	void check_indent();

	Token make_error(const String &p_message);
	void push_error(const String &p_message);
	void push_error(const Token &p_error);
	Token make_paren_error(CharType p_paren);
	Token make_token(Token::Type p_type);
	Token make_literal(const Variant &p_literal);
	Token make_identifier(const StringName &p_identifier);
	Token check_vcs_marker(CharType p_test, Token::Type p_double_type);
	void push_paren(CharType p_char);
	bool pop_paren(CharType p_expected);

	void newline(bool p_make_token);
	Token number();
	Token potential_identifier();
	Token string();
	Token annotation();

public:
	Token scan();

	void set_source_code(const String &p_source_code);

	int get_cursor_line() const;
	int get_cursor_column() const;
	void set_cursor_position(int p_line, int p_column);
	void set_multiline_mode(bool p_state);
	bool is_past_cursor() const;
	static String get_token_name(Token::Type p_token_type);

	GDScriptTokenizer();
};

#endif
