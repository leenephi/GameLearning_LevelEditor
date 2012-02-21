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

void StringInput::handle_input(std::string &returning)
{
    SDL_Event event;
    if(event.type == SDL_KEYDOWN)
    {
        std::string temp = str;

        if(str.length() <= 16)
        {
            if(event.key.keysym.unicode == (Uint16)' ')
            {
                str += (char)event.key.keysym.unicode;
            }
                 //If the key is a number
            else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
            //If the key is a uppercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
            //If the key is a lowercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
        }
            //If backspace was pressed and the string isn't blank
        if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
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
    returning = str;
}

void StringInput::OnRender(SDL_Surface* Surf_Display)
{
    //If the surface isn't blank
    if( text != NULL )
    {
        //Show the name
        CSurface::OnDraw(Surf_Display, text, WWIDTH/2, WHEIGHT/2);
    }
}
