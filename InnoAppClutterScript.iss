[Setup]
; --- GENERAL INFO ---
AppName=Clutter Editor
AppVersion=0.0.1
AppPublisher=MathysHymon
DefaultDirName={autopf}\ClutterEditor
DefaultGroupName=Clutter Editor
OutputDir=.\InstallerOutput
OutputBaseFilename=ClutterEditor
SetupIconFile=bin\EditorContent\clutterLogoDownload.ico

ChangesAssociations=yes
Compression=lzma
SolidCompression=yes

[Tasks]
Name: "desktopicon"; Description: "Créer un raccourci sur le bureau"; GroupDescription: "Icônes supplémentaires:"; Flags: unchecked

[Files]
Source: "bin\ClutterEditor.exe"; DestDir: "{app}"; Flags: ignoreversion

; ⚠️ À CHANGER : Mets le vrai chemin relatif vers ton dossier EditorContent source
; L'astérisque à la fin et les flags permettent de prendre tous les sous-dossiers
Source: "bin\EditorContent\*"; DestDir: "{app}\EditorContent"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
; Raccourcis Menu Démarrer et Bureau
Name: "{group}\Clutter Editor"; Filename: "{app}\ClutterEditor.exe"
Name: "{autodesktop}\Clutter Editor"; Filename: "{app}\ClutterEditor.exe"; Tasks: desktopicon

[Registry]

; 1. L'extension .cltProject (pointe vers notre identifiant interne)
Root: HKCR; Subkey: ".cltProject"; ValueType: string; ValueName: ""; ValueData: "ClutterEngine.ProjectFile"; Flags: uninsdeletevalue

; 2. L'identifiant interne (donne le nom "humain" de ton fichier)
Root: HKCR; Subkey: "ClutterEngine.ProjectFile"; ValueType: string; ValueName: ""; ValueData: "Clutter Engine Project"; Flags: uninsdeletekey

; 3. L'Icône du fichier (pointe vers le fichier .ico dans ton dossier d'installation)
; ⚠️ Assure-toi d'avoir bien mis un vrai fichier .ico valide à cet emplacement !
Root: HKCR; Subkey: "ClutterEngine.ProjectFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\EditorContent\clutterLogo.ico"

; 4. L'Action d'ouverture (Le double-clic)
; Les triples guillemets """" sont la façon d'Inno Setup de générer un vrai guillemet dans le registre final pour sécuriser les espaces dans les chemins
Root: HKCR; Subkey: "ClutterEngine.ProjectFile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\ClutterEditor.exe"" ""%1"""