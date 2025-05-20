//
// Created by Baas Zunnaiyyer on 5/20/2025.
//
#pragma once

#include <string>
#include <vector>
#include <bits/locale_facets_nonio.h>

enum class TokenType {
    produce,
    int_lit,
    semi,
    open_paren,
    close_paren,
    ident,
    have,
    eq
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

class Tokenizer {
public:
    inline explicit Tokenizer(const std::string& src)
        : m_src(std::move(src)) {

    }

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;

        std::string buf;
        while (peek().has_value()) {
            if (std::isalpha(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buf.push_back(consume());
                    std::cout << buf << std::endl;
                }

                if (buf == "produce") {
                    tokens.push_back({.type = TokenType::produce});
                    buf.clear();
                    continue;
                }
                else if (buf == "have") {
                    tokens.push_back({.type = TokenType::have});
                    buf.clear();
                    continue;
                }
                else {
                    tokens.push_back({.type = TokenType::ident, .value = buf});
                    buf.clear();
                    continue;
                }

            }
            else if (std::isdigit(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
            }
            else if (peek().value() == '(' ) {
                consume();
                tokens.push_back({.type = TokenType::open_paren});
            }else if (peek().value() == ')' ) {
                consume();
                tokens.push_back({.type = TokenType::close_paren});
            }
            else if (peek().value() == ';') {
                consume();
                tokens.push_back({.type = TokenType::semi});
                continue;
            }
            else if (peek().value() == '=') {
                consume();
                tokens.push_back({.type = TokenType::eq});
                continue;
            }
            else if (std::isspace(peek().value())) {
                std::cout << "Space" << std::endl;
                consume();
                continue;
            }else {
                std::cerr << "you messed Up!" << std::endl;
                exit(EXIT_FAILURE);
            }

        }
        m_index = 0;
        return tokens;
    }

private:

    [[nodiscard]] inline std::optional<char> peek(int offset = 0) const
    {
        if (m_index + offset >= m_src.length()) {
            return {};
        }else {
            return m_src.at(m_index + offset);
        }
    }

    inline char consume() {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    size_t m_index = 0;
};