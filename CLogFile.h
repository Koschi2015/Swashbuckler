/* Logfile Klasse die in HTML format die Daten in einer Datei ablegt */
#ifndef CLOGFILE_H
#define CLOGFILE_H

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

enum en_LogFileFormat { LFF_RED,        // Rot
                        LFF_BLUE,       // Blau
                        LFF_GREEN,      // Grün
                        LFF_BLACK,      // Schwarz
                        LFF_NAVY,
                        LFF_YELLOW,
                        LFF_MAROON,
                        LFF_OLIVE,
                        LFF_PURPLE,
                        LFF_TEAL,
                        LFF_GRAY,
                        LFF_SILVER,
                        LFF_LIME,
                        LFF_FUCHSIA,
                        LFF_AQUA,
                        LFF_WHITE,
                        LFF_BOLD_ON,
                        LFF_BOLD_OFF,
                        LFF_ITALIC_ON,
                        LFF_ITALIC_OFF,
                        LFF_UNDERLINE_ON,
                        LFF_UNDERLINE_OFF,
                        LFF_STANDARD,
                       };


class CLogFile
{
private:
    // Text der in die Datei soll
    std::fstream MyFile;
public:
    void Creat_LogFile(std::string File);
    void Write(std::string Text);
    // Überladen des Eingangsoperator
    //std::ostream& operator<<( bool rhs);
    std::ostream& operator<<( int rhs);
    std::ostream& operator<<( long rhs);
    std::ostream& operator<<( float rhs);
    std::ostream& operator<<( double rhs);
    std::ostream& operator<<( std::string rhs);
    std::ostream& operator<<( en_LogFileFormat rhs);
    static std::string endl();
    CLogFile() {};
    ~CLogFile() {MyFile.close();}
};

#endif // Ende CLOGFILE_H
