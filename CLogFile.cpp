#include "CLogFile.h"

void CLogFile::Creat_LogFile(std::string File)
{
    MyFile.open(File.c_str(), std::ios::out);
    MyFile << "<html><head><title>Logfile</title></head>";
    MyFile << "<body><font face='courier new'>";
    MyFile << "Logfile \"" << File << "\" created <br>" << std::endl;
    #ifdef _DEBUG
        MyFile << "Build: Debug<br><br>" << std::endl;
    #else
        MyFile << "Build: Release<br><br>" << std::endl;
    #endif
    MyFile << "If there any problems please <a href='mailto:Koschi_2@web.de?subject=Logfile'>";
    MyFile << "send me a E-Mail</a> with the Logfile.html<br><br>" << std::endl;
}
void CLogFile::Write(std::string Text)
{
    if(MyFile.is_open())
    {
        MyFile << Text << "<br>"<< std::endl;;
    }
}
std::ostream& CLogFile::operator<<( int rhs)
{
    MyFile << rhs << std::endl;
    return MyFile;
}
std::ostream& CLogFile::operator<<( float rhs)
{
    MyFile << rhs << std::endl;
    return MyFile;
}
std::ostream& CLogFile::operator<<( double rhs)
{
    MyFile << rhs << std::endl;
    return MyFile;
}
std::ostream& CLogFile::operator<<( std::string rhs)
{
    MyFile << rhs << std::endl;
    return MyFile;
}
std::ostream& CLogFile::operator<<( long rhs)
{
    MyFile << rhs << std::endl;
    return MyFile;
}
std::string CLogFile::endl()
{
    std::string out = "<br>";
    return out;
}
std::ostream& CLogFile::operator<<(en_LogFileFormat rhs)
{
    switch(rhs)
    {
        case LFF_BLUE:
        MyFile << "<font color=blue>" << std::endl;
        return MyFile;
        break;
        case LFF_RED:
        MyFile << "<font color=red>" << std::endl;
        return MyFile;
        break;
        case LFF_GREEN:
        MyFile << "<font color=green>" << std::endl;
        return MyFile;
        break;
        case LFF_BLACK:
        MyFile << "<font color=black>" << std::endl;
        return MyFile;
        break;
        case LFF_NAVY:
        MyFile << "<font color=navy>" << std::endl;
        return MyFile;
        break;
        case LFF_YELLOW:
        MyFile << "<font color=yellow>" << std::endl;
        return MyFile;
        break;
        case LFF_MAROON:
        MyFile << "<font color=maroon>" << std::endl;
        return MyFile;
        break;
        case LFF_GRAY:
        MyFile << "<font color=gray>" << std::endl;
        return MyFile;
        break;
        case LFF_SILVER:
        MyFile << "<font color=silver>" << std::endl;
        return MyFile;
        break;
        case LFF_AQUA:
        MyFile << "<font color=aqua>" << std::endl;
        return MyFile;
        break;
        case LFF_FUCHSIA:
        MyFile << "<font color=fuchsia>" << std::endl;
        return MyFile;
        break;
        case LFF_WHITE:
        MyFile << "<font color=white>" << std::endl;
        return MyFile;
        break;
        case LFF_LIME:
        MyFile << "<font color=lime>" << std::endl;
        return MyFile;
        break;
        case LFF_PURPLE:
        MyFile << "<font color=purple>" << std::endl;
        return MyFile;
        break;
        case LFF_OLIVE:
        MyFile << "<font color=olive>" << std::endl;
        return MyFile;
        case LFF_BOLD_ON:
        MyFile << "<b>" << std::endl;
        return MyFile;
        break;
        case LFF_BOLD_OFF:
        MyFile << "</b>" << std::endl;
        return MyFile;
        break;
        case LFF_ITALIC_ON:
        MyFile << "<i>" << std::endl;
        return MyFile;
        break;
        case LFF_ITALIC_OFF:
        MyFile << "</i>" << std::endl;
        return MyFile;
        break;
        case LFF_UNDERLINE_ON:
        MyFile << "<u>" << std::endl;
        return MyFile;
        break;
        case LFF_UNDERLINE_OFF:
        MyFile << "</u>" << std::endl;
        return MyFile;
        break;
        case LFF_STANDARD:
        MyFile << "</u></i></b> <font color=black> " << std::endl;
        return MyFile;
        break;
        default:
        MyFile << "<font color=black>" << std::endl;
        return MyFile;
    }
}
