#include "CApp.h"

StringInput StringInput::input;

StringInput::StringInput()
{
    str = "";

    text = NULL;

    SDL_EnableUNICODE( SDL_ENABLE);
}
StringInput::~StringInput()
{
    SDL_FreeSurface(text);

    SDL_EnableUNICODE(SDL_DISABLE);
}

 StringInput::handle_input(SDLKey sym, Uint16 unicode)
{
        std::string temp = str;

        if(str.length() <= 16)
        {
            if(unicode == (Uint16)' ')
            {
                str += (char)unicode;
            }
                 //If the key is a number
            else if( ( unicode >= (Uint16)'0' ) && ( unicode <= (Uint16)'9' ) )
            {
                //Append the character
                str += (char)unicode;
            }
            //If the key is a uppercase letter
            else if( ( unicode >= (Uint16)'A' ) && ( unicode <= (Uint16)'Z' ) )
            {
                //Append the character
                str += (char)unicode;
            }
            //If the key is a lowercase letter
            else if( ( unicode >= (Uint16)'a' ) && ( unicode <= (Uint16)'z' ) )
            {
                //Append the character
                str += (char)unicode;
            }
        }
            //If backspace was pressed and the string isn't blank
        if( ( sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
        {
            //Remove a character from the end
            str.erase( str.length() - 1 );
        }
            //If the string was changed
        if( str != temp )
        {
            //Free the old surface
            SDL_FreeSurface( text );

            TTF_Font*       font;
            font = TTF_OpenFont( "FOO.ttf", 28 );
            SDL_Color       textColor;
            textColor = {255, 255, 255 };

            //Render a new text surface
            text = TTF_RenderText_Solid( font, str.c_str(), textColor );
        }
}

void StringInput::OnRender(SDL_Surface* Surf_Display)
{
    //If the surface isn't blank

        //Show the name
        TTF_Font*       font;
            font = TTF_OpenFont( "FOO.ttf", 28 );
            SDL_Color       textColor;
            textColor = {255, 255, 255 };
        text = TTF_RenderText_Solid( font, str.c_str(), textColor );
        CSurface::OnDraw(Surf_Display, text, WWIDTH/2, WHEIGHT/2);

}
