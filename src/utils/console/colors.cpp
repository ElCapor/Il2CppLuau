#include "colors.hpp"

namespace hue
{
    inline bool is_good(int c)
    {
        return 0 <= c && c < 256;
    }

    inline int itoc(int c)
    {
        return is_good(c) ? c : BAD_COLOR;
    }

    inline int itoc(int a, int b)
    {
        return itoc(a + b * 16);
    }

    // std::string to color
    int stoc(std::string a)
    {
        // convert s to lowercase, and format variants like  "light_blue"
        std::transform(a.begin(), a.end(), a.begin(), [](char c)
            {
                if ('A' <= c && c <= 'Z')
                    c = c - 'A' + 'a';
                else if (c == '_' || c == '-')
                    c = ' ';
                return c;
            });

        // operator[] on std::map is non-const, use std::map::at instead
        return (CODES.find(a) != CODES.end()) ? CODES.at(a) : BAD_COLOR;
    }

    int stoc(std::string a, std::string b)
    {
        return itoc(stoc(a), stoc(b));
    }

    std::string ctos(int c)
    {
        return (0 <= c && c < 256) ?
            "(text) " + NAMES.at(c % 16) + " + " +
            "(background) " + NAMES.at(c / 16) :
            "BAD COLOR";
    }

    int get()
    {
        CONSOLE_SCREEN_BUFFER_INFO i;
        return GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &i) ?
            i.wAttributes : BAD_COLOR;
    }

    int get_text()
    {
        return (get() != BAD_COLOR) ? get() % 16 : BAD_COLOR;
    }

    int get_background()
    {
        return (get() != BAD_COLOR) ? get() / 16 : BAD_COLOR;
    }

    void set(int c)
    {
        if (is_good(c))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }

    void set(int a, int b)
    {
        set(a + b * 16);
    }

    void set(std::string a, std::string b)
    {
        set(stoc(a) + stoc(b) * 16);
    }

    void set_text(std::string a)
    {
        set(stoc(a), get_background());
    }

    void set_background(std::string b)
    {
        set(get_text(), stoc(b));
    }

    void reset()
    {
        set(DEFAULT_COLOR);
    }

    int invert(int c)
    {
        if (is_good(c)) {
            int a = c % 16;
            int b = c / 16;
            return b + a * 16;
        }
        else
            return BAD_COLOR;
    }

    std::ostream& reset(std::ostream& os) { reset();                return os; }
    std::ostream& black(std::ostream& os) { set_text("k");          return os; }
    std::ostream& blue(std::ostream& os) { set_text("b");          return os; }
    std::ostream& green(std::ostream& os) { set_text("g");          return os; }
    std::ostream& aqua(std::ostream& os) { set_text("a");          return os; }
    std::ostream& red(std::ostream& os) { set_text("r");          return os; }
    std::ostream& purple(std::ostream& os) { set_text("p");          return os; }
    std::ostream& yellow(std::ostream& os) { set_text("y");          return os; }
    std::ostream& white(std::ostream& os) { set_text("w");          return os; }
    std::ostream& grey(std::ostream& os) { set_text("e");          return os; }
    std::ostream& light_blue(std::ostream& os) { set_text("lb");         return os; }
    std::ostream& light_green(std::ostream& os) { set_text("lg");         return os; }
    std::ostream& light_aqua(std::ostream& os) { set_text("la");         return os; }
    std::ostream& light_red(std::ostream& os) { set_text("lr");         return os; }
    std::ostream& light_purple(std::ostream& os) { set_text("lp");         return os; }
    std::ostream& light_yellow(std::ostream& os) { set_text("ly");         return os; }
    std::ostream& bright_white(std::ostream& os) { set_text("bw");         return os; }
    std::ostream& on_black(std::ostream& os) { set_background("k");    return os; }
    std::ostream& on_blue(std::ostream& os) { set_background("b");    return os; }
    std::ostream& on_green(std::ostream& os) { set_background("g");    return os; }
    std::ostream& on_aqua(std::ostream& os) { set_background("a");    return os; }
    std::ostream& on_red(std::ostream& os) { set_background("r");    return os; }
    std::ostream& on_purple(std::ostream& os) { set_background("p");    return os; }
    std::ostream& on_yellow(std::ostream& os) { set_background("y");    return os; }
    std::ostream& on_white(std::ostream& os) { set_background("w");    return os; }
    std::ostream& on_grey(std::ostream& os) { set_background("e");    return os; }
    std::ostream& on_light_blue(std::ostream& os) { set_background("lb");   return os; }
    std::ostream& on_light_green(std::ostream& os) { set_background("lg");   return os; }
    std::ostream& on_light_aqua(std::ostream& os) { set_background("la");   return os; }
    std::ostream& on_light_red(std::ostream& os) { set_background("lr");   return os; }
    std::ostream& on_light_purple(std::ostream& os) { set_background("lp");   return os; }
    std::ostream& on_light_yellow(std::ostream& os) { set_background("ly");   return os; }
    std::ostream& on_bright_white(std::ostream& os) { set_background("bw");   return os; }
    std::ostream& black_on_black(std::ostream& os) { set("k", "k");   return os; }
    std::ostream& black_on_blue(std::ostream& os) { set("k", "b");   return os; }
    std::ostream& black_on_green(std::ostream& os) { set("k", "g");   return os; }
    std::ostream& black_on_aqua(std::ostream& os) { set("k", "a");   return os; }
    std::ostream& black_on_red(std::ostream& os) { set("k", "r");   return os; }
    std::ostream& black_on_purple(std::ostream& os) { set("k", "p");   return os; }
    std::ostream& black_on_yellow(std::ostream& os) { set("k", "y");   return os; }
    std::ostream& black_on_white(std::ostream& os) { set("k", "w");   return os; }
    std::ostream& black_on_grey(std::ostream& os) { set("k", "e");   return os; }
    std::ostream& black_on_light_blue(std::ostream& os) { set("k", "lb");  return os; }
    std::ostream& black_on_light_green(std::ostream& os) { set("k", "lg");  return os; }
    std::ostream& black_on_light_aqua(std::ostream& os) { set("k", "la");  return os; }
    std::ostream& black_on_light_red(std::ostream& os) { set("k", "lr");  return os; }
    std::ostream& black_on_light_purple(std::ostream& os) { set("k", "lp");  return os; }
    std::ostream& black_on_light_yellow(std::ostream& os) { set("k", "ly");  return os; }
    std::ostream& black_on_bright_white(std::ostream& os) { set("k", "bw");  return os; }
    std::ostream& blue_on_black(std::ostream& os) { set("b", "k");   return os; }
    std::ostream& blue_on_blue(std::ostream& os) { set("b", "b");   return os; }
    std::ostream& blue_on_green(std::ostream& os) { set("b", "g");   return os; }
    std::ostream& blue_on_aqua(std::ostream& os) { set("b", "a");   return os; }
    std::ostream& blue_on_red(std::ostream& os) { set("b", "r");   return os; }
    std::ostream& blue_on_purple(std::ostream& os) { set("b", "p");   return os; }
    std::ostream& blue_on_yellow(std::ostream& os) { set("b", "y");   return os; }
    std::ostream& blue_on_white(std::ostream& os) { set("b", "w");   return os; }
    std::ostream& blue_on_grey(std::ostream& os) { set("b", "e");   return os; }
    std::ostream& blue_on_light_blue(std::ostream& os) { set("b", "lb");  return os; }
    std::ostream& blue_on_light_green(std::ostream& os) { set("b", "lg");  return os; }
    std::ostream& blue_on_light_aqua(std::ostream& os) { set("b", "la");  return os; }
    std::ostream& blue_on_light_red(std::ostream& os) { set("b", "lr");  return os; }
    std::ostream& blue_on_light_purple(std::ostream& os) { set("b", "lp");  return os; }
    std::ostream& blue_on_light_yellow(std::ostream& os) { set("b", "ly");  return os; }
    std::ostream& blue_on_bright_white(std::ostream& os) { set("b", "bw");  return os; }
    std::ostream& green_on_black(std::ostream& os) { set("g", "k");   return os; }
    std::ostream& green_on_blue(std::ostream& os) { set("g", "b");   return os; }
    std::ostream& green_on_green(std::ostream& os) { set("g", "g");   return os; }
    std::ostream& green_on_aqua(std::ostream& os) { set("g", "a");   return os; }
    std::ostream& green_on_red(std::ostream& os) { set("g", "r");   return os; }
    std::ostream& green_on_purple(std::ostream& os) { set("g", "p");   return os; }
    std::ostream& green_on_yellow(std::ostream& os) { set("g", "y");   return os; }
    std::ostream& green_on_white(std::ostream& os) { set("g", "w");   return os; }
    std::ostream& green_on_grey(std::ostream& os) { set("g", "e");   return os; }
    std::ostream& green_on_light_blue(std::ostream& os) { set("g", "lb");  return os; }
    std::ostream& green_on_light_green(std::ostream& os) { set("g", "lg");  return os; }
    std::ostream& green_on_light_aqua(std::ostream& os) { set("g", "la");  return os; }
    std::ostream& green_on_light_red(std::ostream& os) { set("g", "lr");  return os; }
    std::ostream& green_on_light_purple(std::ostream& os) { set("g", "lp");  return os; }
    std::ostream& green_on_light_yellow(std::ostream& os) { set("g", "ly");  return os; }
    std::ostream& green_on_bright_white(std::ostream& os) { set("g", "bw");  return os; }
    std::ostream& aqua_on_black(std::ostream& os) { set("a", "k");   return os; }
    std::ostream& aqua_on_blue(std::ostream& os) { set("a", "b");   return os; }
    std::ostream& aqua_on_green(std::ostream& os) { set("a", "g");   return os; }
    std::ostream& aqua_on_aqua(std::ostream& os) { set("a", "a");   return os; }
    std::ostream& aqua_on_red(std::ostream& os) { set("a", "r");   return os; }
    std::ostream& aqua_on_purple(std::ostream& os) { set("a", "p");   return os; }
    std::ostream& aqua_on_yellow(std::ostream& os) { set("a", "y");   return os; }
    std::ostream& aqua_on_white(std::ostream& os) { set("a", "w");   return os; }
    std::ostream& aqua_on_grey(std::ostream& os) { set("a", "e");   return os; }
    std::ostream& aqua_on_light_blue(std::ostream& os) { set("a", "lb");  return os; }
    std::ostream& aqua_on_light_green(std::ostream& os) { set("a", "lg");  return os; }
    std::ostream& aqua_on_light_aqua(std::ostream& os) { set("a", "la");  return os; }
    std::ostream& aqua_on_light_red(std::ostream& os) { set("a", "lr");  return os; }
    std::ostream& aqua_on_light_purple(std::ostream& os) { set("a", "lp");  return os; }
    std::ostream& aqua_on_light_yellow(std::ostream& os) { set("a", "ly");  return os; }
    std::ostream& aqua_on_bright_white(std::ostream& os) { set("a", "bw");  return os; }
    std::ostream& red_on_black(std::ostream& os) { set("r", "k");   return os; }
    std::ostream& red_on_blue(std::ostream& os) { set("r", "b");   return os; }
    std::ostream& red_on_green(std::ostream& os) { set("r", "g");   return os; }
    std::ostream& red_on_aqua(std::ostream& os) { set("r", "a");   return os; }
    std::ostream& red_on_red(std::ostream& os) { set("r", "r");   return os; }
    std::ostream& red_on_purple(std::ostream& os) { set("r", "p");   return os; }
    std::ostream& red_on_yellow(std::ostream& os) { set("r", "y");   return os; }
    std::ostream& red_on_white(std::ostream& os) { set("r", "w");   return os; }
    std::ostream& red_on_grey(std::ostream& os) { set("r", "e");   return os; }
    std::ostream& red_on_light_blue(std::ostream& os) { set("r", "lb");  return os; }
    std::ostream& red_on_light_green(std::ostream& os) { set("r", "lg");  return os; }
    std::ostream& red_on_light_aqua(std::ostream& os) { set("r", "la");  return os; }
    std::ostream& red_on_light_red(std::ostream& os) { set("r", "lr");  return os; }
    std::ostream& red_on_light_purple(std::ostream& os) { set("r", "lp");  return os; }
    std::ostream& red_on_light_yellow(std::ostream& os) { set("r", "ly");  return os; }
    std::ostream& red_on_bright_white(std::ostream& os) { set("r", "bw");  return os; }
    std::ostream& purple_on_black(std::ostream& os) { set("p", "k");   return os; }
    std::ostream& purple_on_blue(std::ostream& os) { set("p", "b");   return os; }
    std::ostream& purple_on_green(std::ostream& os) { set("p", "g");   return os; }
    std::ostream& purple_on_aqua(std::ostream& os) { set("p", "a");   return os; }
    std::ostream& purple_on_red(std::ostream& os) { set("p", "r");   return os; }
    std::ostream& purple_on_purple(std::ostream& os) { set("p", "p");   return os; }
    std::ostream& purple_on_yellow(std::ostream& os) { set("p", "y");   return os; }
    std::ostream& purple_on_white(std::ostream& os) { set("p", "w");   return os; }
    std::ostream& purple_on_grey(std::ostream& os) { set("p", "e");   return os; }
    std::ostream& purple_on_light_blue(std::ostream& os) { set("p", "lb");  return os; }
    std::ostream& purple_on_light_green(std::ostream& os) { set("p", "lg");  return os; }
    std::ostream& purple_on_light_aqua(std::ostream& os) { set("p", "la");  return os; }
    std::ostream& purple_on_light_red(std::ostream& os) { set("p", "lr");  return os; }
    std::ostream& purple_on_light_purple(std::ostream& os) { set("p", "lp");  return os; }
    std::ostream& purple_on_light_yellow(std::ostream& os) { set("p", "ly");  return os; }
    std::ostream& purple_on_bright_white(std::ostream& os) { set("p", "bw");  return os; }
    std::ostream& yellow_on_black(std::ostream& os) { set("y", "k");   return os; }
    std::ostream& yellow_on_blue(std::ostream& os) { set("y", "b");   return os; }
    std::ostream& yellow_on_green(std::ostream& os) { set("y", "g");   return os; }
    std::ostream& yellow_on_aqua(std::ostream& os) { set("y", "a");   return os; }
    std::ostream& yellow_on_red(std::ostream& os) { set("y", "r");   return os; }
    std::ostream& yellow_on_purple(std::ostream& os) { set("y", "p");   return os; }
    std::ostream& yellow_on_yellow(std::ostream& os) { set("y", "y");   return os; }
    std::ostream& yellow_on_white(std::ostream& os) { set("y", "w");   return os; }
    std::ostream& yellow_on_grey(std::ostream& os) { set("y", "e");   return os; }
    std::ostream& yellow_on_light_blue(std::ostream& os) { set("y", "lb");  return os; }
    std::ostream& yellow_on_light_green(std::ostream& os) { set("y", "lg");  return os; }
    std::ostream& yellow_on_light_aqua(std::ostream& os) { set("y", "la");  return os; }
    std::ostream& yellow_on_light_red(std::ostream& os) { set("y", "lr");  return os; }
    std::ostream& yellow_on_light_purple(std::ostream& os) { set("y", "lp");  return os; }
    std::ostream& yellow_on_light_yellow(std::ostream& os) { set("y", "ly");  return os; }
    std::ostream& yellow_on_bright_white(std::ostream& os) { set("y", "bw");  return os; }
    std::ostream& white_on_black(std::ostream& os) { set("w", "k");   return os; }
    std::ostream& white_on_blue(std::ostream& os) { set("w", "b");   return os; }
    std::ostream& white_on_green(std::ostream& os) { set("w", "g");   return os; }
    std::ostream& white_on_aqua(std::ostream& os) { set("w", "a");   return os; }
    std::ostream& white_on_red(std::ostream& os) { set("w", "r");   return os; }
    std::ostream& white_on_purple(std::ostream& os) { set("w", "p");   return os; }
    std::ostream& white_on_yellow(std::ostream& os) { set("w", "y");   return os; }
    std::ostream& white_on_white(std::ostream& os) { set("w", "w");   return os; }
    std::ostream& white_on_grey(std::ostream& os) { set("w", "e");   return os; }
    std::ostream& white_on_light_blue(std::ostream& os) { set("w", "lb");  return os; }
    std::ostream& white_on_light_green(std::ostream& os) { set("w", "lg");  return os; }
    std::ostream& white_on_light_aqua(std::ostream& os) { set("w", "la");  return os; }
    std::ostream& white_on_light_red(std::ostream& os) { set("w", "lr");  return os; }
    std::ostream& white_on_light_purple(std::ostream& os) { set("w", "lp");  return os; }
    std::ostream& white_on_light_yellow(std::ostream& os) { set("w", "ly");  return os; }
    std::ostream& white_on_bright_white(std::ostream& os) { set("w", "bw");  return os; }
    std::ostream& grey_on_black(std::ostream& os) { set("e", "k");   return os; }
    std::ostream& grey_on_blue(std::ostream& os) { set("e", "b");   return os; }
    std::ostream& grey_on_green(std::ostream& os) { set("e", "g");   return os; }
    std::ostream& grey_on_aqua(std::ostream& os) { set("e", "a");   return os; }
    std::ostream& grey_on_red(std::ostream& os) { set("e", "r");   return os; }
    std::ostream& grey_on_purple(std::ostream& os) { set("e", "p");   return os; }
    std::ostream& grey_on_yellow(std::ostream& os) { set("e", "y");   return os; }
    std::ostream& grey_on_white(std::ostream& os) { set("e", "w");   return os; }
    std::ostream& grey_on_grey(std::ostream& os) { set("e", "e");   return os; }
    std::ostream& grey_on_light_blue(std::ostream& os) { set("e", "lb");  return os; }
    std::ostream& grey_on_light_green(std::ostream& os) { set("e", "lg");  return os; }
    std::ostream& grey_on_light_aqua(std::ostream& os) { set("e", "la");  return os; }
    std::ostream& grey_on_light_red(std::ostream& os) { set("e", "lr");  return os; }
    std::ostream& grey_on_light_purple(std::ostream& os) { set("e", "lp");  return os; }
    std::ostream& grey_on_light_yellow(std::ostream& os) { set("e", "ly");  return os; }
    std::ostream& grey_on_bright_white(std::ostream& os) { set("e", "bw");  return os; }
    std::ostream& light_blue_on_black(std::ostream& os) { set("lb", "k");  return os; }
    std::ostream& light_blue_on_blue(std::ostream& os) { set("lb", "b");  return os; }
    std::ostream& light_blue_on_green(std::ostream& os) { set("lb", "g");  return os; }
    std::ostream& light_blue_on_aqua(std::ostream& os) { set("lb", "a");  return os; }
    std::ostream& light_blue_on_red(std::ostream& os) { set("lb", "r");  return os; }
    std::ostream& light_blue_on_purple(std::ostream& os) { set("lb", "p");  return os; }
    std::ostream& light_blue_on_yellow(std::ostream& os) { set("lb", "y");  return os; }
    std::ostream& light_blue_on_white(std::ostream& os) { set("lb", "w");  return os; }
    std::ostream& light_blue_on_grey(std::ostream& os) { set("lb", "e");  return os; }
    std::ostream& light_blue_on_light_blue(std::ostream& os) { set("lb", "lb"); return os; }
    std::ostream& light_blue_on_light_green(std::ostream& os) { set("lb", "lg"); return os; }
    std::ostream& light_blue_on_light_aqua(std::ostream& os) { set("lb", "la"); return os; }
    std::ostream& light_blue_on_light_red(std::ostream& os) { set("lb", "lr"); return os; }
    std::ostream& light_blue_on_light_purple(std::ostream& os) { set("lb", "lp"); return os; }
    std::ostream& light_blue_on_light_yellow(std::ostream& os) { set("lb", "ly"); return os; }
    std::ostream& light_blue_on_bright_white(std::ostream& os) { set("lb", "bw"); return os; }
    std::ostream& light_green_on_black(std::ostream& os) { set("lg", "k");  return os; }
    std::ostream& light_green_on_blue(std::ostream& os) { set("lg", "b");  return os; }
    std::ostream& light_green_on_green(std::ostream& os) { set("lg", "g");  return os; }
    std::ostream& light_green_on_aqua(std::ostream& os) { set("lg", "a");  return os; }
    std::ostream& light_green_on_red(std::ostream& os) { set("lg", "r");  return os; }
    std::ostream& light_green_on_purple(std::ostream& os) { set("lg", "p");  return os; }
    std::ostream& light_green_on_yellow(std::ostream& os) { set("lg", "y");  return os; }
    std::ostream& light_green_on_white(std::ostream& os) { set("lg", "w");  return os; }
    std::ostream& light_green_on_grey(std::ostream& os) { set("lg", "e");  return os; }
    std::ostream& light_green_on_light_blue(std::ostream& os) { set("lg", "lb"); return os; }
    std::ostream& light_green_on_light_green(std::ostream& os) { set("lg", "lg"); return os; }
    std::ostream& light_green_on_light_aqua(std::ostream& os) { set("lg", "la"); return os; }
    std::ostream& light_green_on_light_red(std::ostream& os) { set("lg", "lr"); return os; }
    std::ostream& light_green_on_light_purple(std::ostream& os) { set("lg", "lp"); return os; }
    std::ostream& light_green_on_light_yellow(std::ostream& os) { set("lg", "ly"); return os; }
    std::ostream& light_green_on_bright_white(std::ostream& os) { set("lg", "bw"); return os; }
    std::ostream& light_aqua_on_black(std::ostream& os) { set("la", "k");  return os; }
    std::ostream& light_aqua_on_blue(std::ostream& os) { set("la", "b");  return os; }
    std::ostream& light_aqua_on_green(std::ostream& os) { set("la", "g");  return os; }
    std::ostream& light_aqua_on_aqua(std::ostream& os) { set("la", "a");  return os; }
    std::ostream& light_aqua_on_red(std::ostream& os) { set("la", "r");  return os; }
    std::ostream& light_aqua_on_purple(std::ostream& os) { set("la", "p");  return os; }
    std::ostream& light_aqua_on_yellow(std::ostream& os) { set("la", "y");  return os; }
    std::ostream& light_aqua_on_white(std::ostream& os) { set("la", "w");  return os; }
    std::ostream& light_aqua_on_grey(std::ostream& os) { set("la", "e");  return os; }
    std::ostream& light_aqua_on_light_blue(std::ostream& os) { set("la", "lb"); return os; }
    std::ostream& light_aqua_on_light_green(std::ostream& os) { set("la", "lg"); return os; }
    std::ostream& light_aqua_on_light_aqua(std::ostream& os) { set("la", "la"); return os; }
    std::ostream& light_aqua_on_light_red(std::ostream& os) { set("la", "lr"); return os; }
    std::ostream& light_aqua_on_light_purple(std::ostream& os) { set("la", "lp"); return os; }
    std::ostream& light_aqua_on_light_yellow(std::ostream& os) { set("la", "ly"); return os; }
    std::ostream& light_aqua_on_bright_white(std::ostream& os) { set("la", "bw"); return os; }
    std::ostream& light_red_on_black(std::ostream& os) { set("lr", "k");  return os; }
    std::ostream& light_red_on_blue(std::ostream& os) { set("lr", "b");  return os; }
    std::ostream& light_red_on_green(std::ostream& os) { set("lr", "g");  return os; }
    std::ostream& light_red_on_aqua(std::ostream& os) { set("lr", "a");  return os; }
    std::ostream& light_red_on_red(std::ostream& os) { set("lr", "r");  return os; }
    std::ostream& light_red_on_purple(std::ostream& os) { set("lr", "p");  return os; }
    std::ostream& light_red_on_yellow(std::ostream& os) { set("lr", "y");  return os; }
    std::ostream& light_red_on_white(std::ostream& os) { set("lr", "w");  return os; }
    std::ostream& light_red_on_grey(std::ostream& os) { set("lr", "e");  return os; }
    std::ostream& light_red_on_light_blue(std::ostream& os) { set("lr", "lb"); return os; }
    std::ostream& light_red_on_light_green(std::ostream& os) { set("lr", "lg"); return os; }
    std::ostream& light_red_on_light_aqua(std::ostream& os) { set("lr", "la"); return os; }
    std::ostream& light_red_on_light_red(std::ostream& os) { set("lr", "lr"); return os; }
    std::ostream& light_red_on_light_purple(std::ostream& os) { set("lr", "lp"); return os; }
    std::ostream& light_red_on_light_yellow(std::ostream& os) { set("lr", "ly"); return os; }
    std::ostream& light_red_on_bright_white(std::ostream& os) { set("lr", "bw"); return os; }
    std::ostream& light_purple_on_black(std::ostream& os) { set("lp", "k");  return os; }
    std::ostream& light_purple_on_blue(std::ostream& os) { set("lp", "b");  return os; }
    std::ostream& light_purple_on_green(std::ostream& os) { set("lp", "g");  return os; }
    std::ostream& light_purple_on_aqua(std::ostream& os) { set("lp", "a");  return os; }
    std::ostream& light_purple_on_red(std::ostream& os) { set("lp", "r");  return os; }
    std::ostream& light_purple_on_purple(std::ostream& os) { set("lp", "p");  return os; }
    std::ostream& light_purple_on_yellow(std::ostream& os) { set("lp", "y");  return os; }
    std::ostream& light_purple_on_white(std::ostream& os) { set("lp", "w");  return os; }
    std::ostream& light_purple_on_grey(std::ostream& os) { set("lp", "e");  return os; }
    std::ostream& light_purple_on_light_blue(std::ostream& os) { set("lp", "lb"); return os; }
    std::ostream& light_purple_on_light_green(std::ostream& os) { set("lp", "lg"); return os; }
    std::ostream& light_purple_on_light_aqua(std::ostream& os) { set("lp", "la"); return os; }
    std::ostream& light_purple_on_light_red(std::ostream& os) { set("lp", "lr"); return os; }
    std::ostream& light_purple_on_light_purple(std::ostream& os) { set("lp", "lp"); return os; }
    std::ostream& light_purple_on_light_yellow(std::ostream& os) { set("lp", "ly"); return os; }
    std::ostream& light_purple_on_bright_white(std::ostream& os) { set("lp", "bw"); return os; }
    std::ostream& light_yellow_on_black(std::ostream& os) { set("ly", "k");  return os; }
    std::ostream& light_yellow_on_blue(std::ostream& os) { set("ly", "b");  return os; }
    std::ostream& light_yellow_on_green(std::ostream& os) { set("ly", "g");  return os; }
    std::ostream& light_yellow_on_aqua(std::ostream& os) { set("ly", "a");  return os; }
    std::ostream& light_yellow_on_red(std::ostream& os) { set("ly", "r");  return os; }
    std::ostream& light_yellow_on_purple(std::ostream& os) { set("ly", "p");  return os; }
    std::ostream& light_yellow_on_yellow(std::ostream& os) { set("ly", "y");  return os; }
    std::ostream& light_yellow_on_white(std::ostream& os) { set("ly", "w");  return os; }
    std::ostream& light_yellow_on_grey(std::ostream& os) { set("ly", "e");  return os; }
    std::ostream& light_yellow_on_light_blue(std::ostream& os) { set("ly", "lb"); return os; }
    std::ostream& light_yellow_on_light_green(std::ostream& os) { set("ly", "lg"); return os; }
    std::ostream& light_yellow_on_light_aqua(std::ostream& os) { set("ly", "la"); return os; }
    std::ostream& light_yellow_on_light_red(std::ostream& os) { set("ly", "lr"); return os; }
    std::ostream& light_yellow_on_light_purple(std::ostream& os) { set("ly", "lp"); return os; }
    std::ostream& light_yellow_on_light_yellow(std::ostream& os) { set("ly", "ly"); return os; }
    std::ostream& light_yellow_on_bright_white(std::ostream& os) { set("ly", "bw"); return os; }
    std::ostream& bright_white_on_black(std::ostream& os) { set("bw", "k");  return os; }
    std::ostream& bright_white_on_blue(std::ostream& os) { set("bw", "b");  return os; }
    std::ostream& bright_white_on_green(std::ostream& os) { set("bw", "g");  return os; }
    std::ostream& bright_white_on_aqua(std::ostream& os) { set("bw", "a");  return os; }
    std::ostream& bright_white_on_red(std::ostream& os) { set("bw", "r");  return os; }
    std::ostream& bright_white_on_purple(std::ostream& os) { set("bw", "p");  return os; }
    std::ostream& bright_white_on_yellow(std::ostream& os) { set("bw", "y");  return os; }
    std::ostream& bright_white_on_white(std::ostream& os) { set("bw", "w");  return os; }
    std::ostream& bright_white_on_grey(std::ostream& os) { set("bw", "e");  return os; }
    std::ostream& bright_white_on_light_blue(std::ostream& os) { set("bw", "lb"); return os; }
    std::ostream& bright_white_on_light_green(std::ostream& os) { set("bw", "lg"); return os; }
    std::ostream& bright_white_on_light_aqua(std::ostream& os) { set("bw", "la"); return os; }
    std::ostream& bright_white_on_light_red(std::ostream& os) { set("bw", "lr"); return os; }
    std::ostream& bright_white_on_light_purple(std::ostream& os) { set("bw", "lp"); return os; }
    std::ostream& bright_white_on_light_yellow(std::ostream& os) { set("bw", "ly"); return os; }
    std::ostream& bright_white_on_bright_white(std::ostream& os) { set("bw", "bw"); return os; }
}