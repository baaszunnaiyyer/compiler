//
// Created by Baas Zunnaiyyer on 5/20/2025.
//
#pragma once

#include <string>
#include <vector>

enum class TokenType {
    produce,
    int_lit,
    semi,
    open_paren,
    close_paren,
    ident,
    have,
    eq,
    plus,
    star,
    minus,
    fslash,
    open_curly,
    close_curly,
    agar,
    warnagar,
    warna,
};

inline std::string to_string(const TokenType type)
{
    switch (type) {
    case TokenType::produce:
        return "`produce`";
    case TokenType::int_lit:
        return "int literal";
    case TokenType::semi:
        return "`;`";
    case TokenType::open_paren:
        return "`(`";
    case TokenType::close_paren:
        return "`)`";
    case TokenType::ident:
        return "identifier";
    case TokenType::have:
        return "`have`";
    case TokenType::eq:
        return "`=`";
    case TokenType::plus:
        return "`+`";
    case TokenType::star:
        return "`*`";
    case TokenType::minus:
        return "`-`";
    case TokenType::fslash:
        return "`/`";
    case TokenType::open_curly:
        return "`{`";
    case TokenType::close_curly:
        return "`}`";
    case TokenType::agar:
        return "`agar`";
    case TokenType::warnagar:
        return "`warnagar`";
    case TokenType::warna:
        return "`warna`";
    }
    assert(false);
}

inline std::optional<int> bin_prec(const TokenType type)
{
    switch (type) {
    case TokenType::minus:
    case TokenType::plus:
        return 0;
    case TokenType::fslash:
    case TokenType::star:
        return 1;
    default:
        return {};
    }
}

struct Token {
    TokenType type;
    int line;
    std::optional<std::string> value {};
};

class Tokenizer {
public:
    explicit Tokenizer(std::string src)
        : m_src(std::move(src))
    {
    }

    std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        std::string buf;
        int line_count = 1;
        while (peek().has_value()) {
            if (std::isalpha(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buf.push_back(consume());
                }
                if (buf == "produce") {
                    tokens.push_back({ TokenType::produce, line_count });
                    buf.clear();
                }
                else if (buf == "have") {
                    tokens.push_back({ TokenType::have, line_count });
                    buf.clear();
                }
                else if (buf == "agar") {
                    tokens.push_back({ TokenType::agar, line_count });
                    buf.clear();
                }
                else if (buf == "warnagar") {
                    tokens.push_back({ TokenType::warnagar, line_count });
                    buf.clear();
                }
                else if (buf == "warna") {
                    tokens.push_back({ TokenType::warna, line_count });
                    buf.clear();
                }
                else {
                    tokens.push_back({ TokenType::ident, line_count, buf });
                    buf.clear();
                }
            }
            else if (std::isdigit(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back({ TokenType::int_lit, line_count, buf });
                buf.clear();
            }
            else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '/') {
                consume();
                consume();
                while (peek().has_value() && peek().value() != '\n') {
                    consume();
                }
            }
            else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '*') {
                consume();
                consume();
                while (peek().has_value()) {
                    if (peek().value() == '*' && peek(1).has_value() && peek(1).value() == '/') {
                        break;
                    }
                    consume();
                }
                if (peek().has_value()) {
                    consume();
                }
                if (peek().has_value()) {
                    consume();
                }
            }
            else if (peek().value() == '(') {
                consume();
                tokens.push_back({ TokenType::open_paren, line_count });
            }
            else if (peek().value() == ')') {
                consume();
                tokens.push_back({ TokenType::close_paren, line_count });
            }
            else if (peek().value() == ';') {
                consume();
                tokens.push_back({ TokenType::semi, line_count });
            }
            else if (peek().value() == '=') {
                consume();
                tokens.push_back({ TokenType::eq, line_count });
            }
            else if (peek().value() == '+') {
                consume();
                tokens.push_back({ TokenType::plus, line_count });
            }
            else if (peek().value() == '*') {
                consume();
                tokens.push_back({ TokenType::star, line_count });
            }
            else if (peek().value() == '-') {
                consume();
                tokens.push_back({ TokenType::minus, line_count });
            }
            else if (peek().value() == '/') {
                consume();
                tokens.push_back({ TokenType::fslash, line_count });
            }
            else if (peek().value() == '{') {
                consume();
                tokens.push_back({ TokenType::open_curly, line_count });
            }
            else if (peek().value() == '}') {
                consume();
                tokens.push_back({ TokenType::close_curly, line_count });
            }
            else if (peek().value() == '\n') {
                consume();
                line_count++;
            }
            else if (std::isspace(peek().value())) {
                consume();
            }
            else {
                std::cerr << "Invalid token" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        m_index = 0;
        return tokens;
    }

private:
    [[nodiscard]] std::optional<char> peek(const size_t offset = 0) const
    {
        if (m_index + offset >= m_src.length()) {
            return {};
        }
        return m_src.at(m_index + offset);
    }

    char consume()
    {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    size_t m_index = 0;
};