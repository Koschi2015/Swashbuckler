#ifndef CSPRITESHEET_H
#define CSPRITESHEET_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "CRessourcenManager.h"
#include "CLogFile.h"



// Spritesheet
class CSpriteSheet
{
private:
	// the Pictrure
	sf::Image* SpriteSheetImg;
	// the Sprite
	sf::Sprite* SpriteSheet;
	// Pfad für die Datei
	std::string Path;
	// Pixel X
	int Pixel_X;
	// Pixel Y
	int Pixel_Y;
	// Image größe X
	int Image_X;
	// Image größe Y
	int Image_Y;
	// Max Images
	int MaxImage;
	// Image Row
	int ImageRow;
	// Image Colum
	int ImageColum;
	// Ressourcen Manager
	static CRessourcenManager* RessourcenManager;
	// true bedeutet Klasse ist Managed von einem Ressourcen Managaer
	static bool Managed;
	//
	static CLogFile* LogFile;
public:
    // Setzt den Ressourcen Manager
    static void Set_RessourcenManager(CRessourcenManager* RM);
	// Load Image
	void Load(std::string Pfad,int SpriteSize_X = 32,int SpriteSize_Y = 32);
	// Gibt das richtige Sprite wieder
	sf::Sprite* operator[] (int Zahl) const;
	// Gibt das richtige Sprite wieder (für Pointer weiß sonst keine andere Lösung)
	sf::Sprite Get_Sprite (int Zahl) const;
	// Sprite Coords
	void Set_Display_Coord(float X,float Y);
	void Set_Display_Coord(int X,int Y);
	// Konstruktor
	CSpriteSheet(void);
	// Destruktor
	~CSpriteSheet(void);
    // KopierKonstruktor
	CSpriteSheet(const CSpriteSheet& Value);
	// Operator ist gleich
	CSpriteSheet operator= (const CSpriteSheet& Value);
	//
	void static Set_LogFile(CLogFile* logfile);
};
// Animatet Sprite
class CAnimateSprite
{
private:
    // Zeitgeber für die Animation
    static sf::Clock Timer;
    // Referenz auf einen SpriteSheet aus dem die einzel Bilder Genommen werden
    CSpriteSheet* Sheet;
    // bei welcher zeit das nächste Bild kommt
    float FrameTime;
    // Zeit die der nächste Frame kommen soll
    float TimeNextFrame;
    // Letztes Bild im Spritesheet
    int LastFrame;
    // Erste Bild im Spritesheet
    int FirstFrame;
    // Bild was Angezeigt wird wenn keine Animation gezeigt werden soll
    int StopFrame;
    // Aktueller Zähler
    int CurrentFrame;
    // true Animation wird gespielt; false StopFrame wird angezeigt
    bool Animation_On;
    #ifdef LOGFILE
    //
	static CLogFile* LogFile;
	#endif
public:
    // Startet / Stoppt Animaation
    void Animation_on(bool Value) {Animation_On = Value;}
    // Setzt das erste Frame
    void Set_FirstFrame(int firstFrame) {FirstFrame = firstFrame;}
    // Setzt das letzte Frame
    void Set_LastFrame(int lastFrame) {LastFrame = lastFrame;}
    // Setzt das Stop Frame
    void Set_StopFrame(int stopFrame) {StopFrame = stopFrame;}
    // Frame time setzen
    void Set_FrameTime(float frameTime) {FrameTime = frameTime;}
    // Gibt den StartFrame Zurück
    int Get_FirstFrame() const {return FirstFrame;}
    // Gibt den LastFrame Zurück
    int Get_LastFrame() const {return LastFrame;}
    // Gibt den StopFrame Zurück
    int Get_StopFrame() const {return StopFrame;}
    // Gibt die zeit wieder die von Bild zu Bild verstreicht
    float Get_FrameTime() const {return FrameTime;}
    //
    sf::Sprite Get_CurrentSprite();
    // Überladen des () Operator um die Animation in der sf::...->Draw() Methode darzustellen
    sf::Sprite operator() ();
    #ifdef LOGFILE
    //
	void static Set_LogFile(CLogFile* logfile);
	#endif
    // default Konstruktor
    CAnimateSprite(CSpriteSheet* Sprite);
    // Konstruktor | SpriteSheet als Referenz, Erste Bild im Spritesheet (für die Animation), Letzte Bild im SpriteSheet (für die Animation), Bild das angezeigt wird wenn keine Animation ist, Zeit die verstreichen soll von einem Bild zum anderen.
    CAnimateSprite(CSpriteSheet* Sprite,int firstFrame,int lastFrame,int stopFrame,float frameTime);
    // Destruktor
    ~CAnimateSprite();

};

#endif //SPRITESHEET_H
