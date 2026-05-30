Signs:

:: - Move in directories

\-- - Comment

\-> - Linked

!! - Alarm

== - Project structure(points 8, 13, 14)





1\. Init



2\. Create Map

OS:: Cursor

UI:: Map



\--No link--





3\. Add Object

Model:: GameObject(UiObject, Rect), Position(Coord),

Items:: Block(Ship)



\-- Rect -> UiObject -> Ship --





4\. Add Level

Levels:: Level(GameLevel, FirstLevel)



\-- GameLevel -> FirstLevel --





5\. Allow Map Move

Controller:: Game

Model:: GameObject, Postion, MapUpdate(MapMovable)



\-- MapMovable -> Ship --





6\. Split Logic n' UI

Controller:: Game, Linker(UIFactory)

Levels:: --REMOVE--

Model:: GameObject(Rect, Ship), Position, MapUpdate(MapMovable, GameMap)

UI:: Map(console\_game\_map), GameObject(console\_ship, console\_ui\_obj), Level(console\_ui\_factory)



\-- GameMap -> console\_game\_map --

\-- Ship -> console\_ship --

\-- console\_ui\_obj -> console\_ship --

\-- UIFactory -> console\_ui\_factory --





7\. Add OS Controlls

OS::API(Settings, Input)

OS::Windows(Settings, Input)

\-- No link --





8\. Add Mario

Model:: GameObject(Movable, Collisionable, Mario), Position, MapUpdate,

UI:: Map, GameObject(console\_mario), Level



\-- Rect -> Movable -> Mario -> console\_mario --

\-- Collisionable -> Mario -> console\_mario --

\-- console\_ui\_obj -> console\_mario --



=================================================================================================================

Controller:: game, ui\_factory



Model:: coord, game\_map, collisionable, rect, ship, movable, mario (speed, map\_movable)



OS::API\&Windows:: os\_control\_settings, user\_input



UI::Console:: console\_game\_map, console\_ui\_factory, console\_ui\_obj, console\_ship, console\_mario



MAIN

=================================================================================================================





9\. Add Adapter

UI:: Map, Level, GameObj, Adapter(console\_ui\_obj\_rect\_adapter)



\-- Rect -> console\_ui\_obj\_rect\_adapter -> console\_mario --

\-- console\_ui\_obj -> console\_ui\_obj\_rect\_adapter -> console\_mario --

\-- Rect -> console\_ui\_obj\_rect\_adapter -> console\_ship --

\-- console\_ui\_obj -> console\_ui\_obj\_rect\_adapter -> console\_ship --



!!!diamond-shaped inheritance!!!

Rect -> Mario -> console\_mario

Rect -> Ship -> console\_ship

Rect -> Adapter -> console\_mario, console\_ship

!!!diamond-shaped inheritance!!!





10\. Add Level

Controller::Levels:: Level(GameLevel, FirstLevel, SecondLevel)

Model:: Position, GameObject, MapUpdate, Linker(UIFactory)



\-- GameLevel -> FirstLevel --

\-- GameLevel -> SecondLevel --





11\. Add EmptyBox n' Adapter

Model:: Position, GameObject(Box), MapUpdate, Linker, Adapter(Rect-MapMove)

UI:: Map, Level, GameObj(console\_box), Adapter



\-- Rect -> Rect-MapMove -> Ship --

\-- MapMovable -> Rect-MapMove -> Ship --

\-- Rect -> Rect-MapMove -> Box -> console\_box --

\-- MapMovable -> Rect-MapMove -> Box -> console\_box --

\-- console\_ui\_obj\_rect\_adapter -> console\_box





12\. Add Enemy

Model:: Position, GameObject(Enemy), MapUpdate, Linker, Adapter

UI:: Map, Level, GameObj(console\_enemy), Adapter



\-- Movable -> Enemy -> console\_enemy --

\-- Collisionable -> Enemy -> console\_enemy --

\-- Adapter -> Enemy -> console\_enemy --

\-- console\_ui\_obj\_rect\_adapter -> console\_enemy --





13\. Add FullBox w' Money

Model:: Position, GameObject(FullBox, Money), MapUpdate, Linker, Adapter

UI:: Map, Level, GameObj(console\_full\_box, console\_money), Adapter



\-- Box -> FullBox -> console\_full\_box --

\-- Collisionable -> FullBox -> console\_full\_box --

\-- Movable -> Money -> console\_money --

\-- Collisionable -> Money -> console\_money --

\-- Adapter -> Money -> console\_money --

\-- console\_ui\_obj\_rect\_adapter -> console\_full\_box --

\-- console\_ui\_obj\_rect\_adapter -> console\_money --



=================================================================================================================

Controller:: game, levels()

Controller::Levels:: game\_level, first\_level, second\_level



Model:: coord, game\_map, rect, map\_movable, rect\_map\_movable\_adapter,

movable, collisionable, box, ship, mario, enemy, full\_box, money (speed, ui\_factory)



OS::API\&Windows:: os\_control\_settings, user\_input



UI::Console:: console\_game\_map, console\_ui\_factory, console\_ui\_obj, console\_ui\_obj\_rect\_adapter,

console\_box, console\_ship, console\_mario, console\_enemy, console\_full\_box, console\_money



MAIN

=================================================================================================================







14 - Refactor structure - Final

=================================================================================================================

Controller:: game



Levels:: game\_level, first\_level, second\_level



Model:: coord, game\_map, map\_movable, rect, rect\_map\_movable\_adapter, movable, collisionable, speed, ui\_factory



Objects:: ship, box, mario, enemy, full\_box, money



OS::API\&Windows:: os\_control\_settings, user\_input



UI::Console:: ui\_objects(), console\_game\_map, console\_ui\_factory, console\_ui\_obj, console\_ui\_obj\_rect\_adapter

UI::Console::UIObjects:: console\_ship, console\_box, console\_mario, console\_enemy, console\_full\_box, console\_money

=================================================================================================================



