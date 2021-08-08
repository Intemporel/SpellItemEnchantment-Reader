# SpellItemEnchantment-Reader
 DBC reader for specific SpellItemEnchantment file
 
 ***
 
 ### How to use ?

Simply insert the `header` file where you want extract some data and define an object with the file path to your `SpellItemEnchantment.dbc`:

```cpp
#include <SpellItemEnchantmentReader/spell_item_enchantment_reader.h>
spell_item_enchantment_reader someData = new spell_item_enchantment_reader(":/binary/dbc/enUS/SpellItemEnchantment.dbc");
```

Now you can use some functions for getting data

```cpp
// return record position for corresponding parameters ID ( Unique ID fields 0 )
quint32 searchRecordByID(uint ID);

// return quint32 value from position in file ( 4 bytes )
quint32 ValueFrom(quint32 pos);

// return quint32 value from coord {record, field} in file ( 4 bytes )
quint32 ValueWhere(quint32 record, quint32 field);

// (you can use searchRecordByID with ID)

// return array corresponding to fiels (2,3,4) in the record index
QVector<quint32> getStatKey(quint32 record );

// return array corresponding to fiels (11,12,13) in the record index
QVector<quint32> getStatType(quint32 record);

// return couple of array corresponding to fiels ( {5,8}, {6,9}, {7,10} ) in the record index
QVector<QVector<quint32>> getStatValue(quint32 record);

// return the only one string's field in the record index
QString getText(quint32 record);
```

I give you an exemple in the `main.cpp`, but for now, that script aren't allowed to extract string data.
Enjoy.
