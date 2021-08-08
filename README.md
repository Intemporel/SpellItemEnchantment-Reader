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
// lang refer to your dbc loc, possibility of lang is contain in enum SpellItemEnchantmentStructure;
// you can use like : 
//                      SpellItemEnchantmentStructure::LANG_enUS or just LANG_enUS
//                      SpellItemEnchantmentStructure::LANG_frFR or just LANG_frFR
//                      ...
quint32 searchRecordByID(uint ID, int lang = LANG_enUS);

// return quint32 value from position in file ( 4 bytes )
quint32 ValueFrom(quint32 pos);

// return quint32 value from coord {record, field} in file ( 4 bytes )
quint32 ValueWhere(quint32 record, quint32 field);

// return array corresponding to fiels (2,3,4) in the record index
QVector<quint32> getStatKey(quint32 record );

// return array corresponding to fiels (11,12,13) in the record index
QVector<quint32> getStatType(quint32 record);

// return couple of array corresponding to fiels ( {5,8}, {6,9}, {7,10} ) in the record index
QVector<QVector<quint32>> getStatValue(quint32 record);

// return the only one string's field in the record index
QString getText(quint32 record);
```

And here there is an simple exemple 

```cpp
spell_item_enchantment_reader data = new spell_item_enchantment_reader(":/binary/dbc/enUS/SpellItemEnchantment.dbc", LANG_enUS);
quint32 record = data->searchRecordByID(266);

qDebug() << "Current cell [" << record << "]";

if (record) {
    QVector<quint32> stat_key = data->getStatKey(record);
    QVector<quint32> stat_type = data->getStatType(record);
    QVector<QVector<quint32>> stat_value = data->getStatValue(record);

    qDebug() << "String [" << data->getText(record); << "]";

    for (int i = 0; i <stat_type.size(); i++)
        qDebug() << "Key [" << stat_key[i] << "] : Type [" << stat_type[i] << "] : Min,Max - [" << stat_value[i][0] << "," << stat_value[i][1] << "]";
}

/* RETURN :

Current cell [ 242 ]
String [ "Fishing Lure (+100 Fishing Skill)" ]
Key [ 3 ] : Type [ 8085 ] : Min,Max - [ 0 , 0 ]
Key [ 0 ] : Type [ 0 ] : Min,Max - [ 0 , 0 ]
Key [ 0 ] : Type [ 0 ] : Min,Max - [ 0 , 0 ]

*/
```
