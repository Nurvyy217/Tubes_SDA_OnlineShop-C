#include <stdio.h>
#include <sqlite3.h>
#include "database.h"

/*

CRUD
1. Insert
2. Update
3. Select
4. Delete
5. SELECT JOIN (opt)

*/

void init_db(sqlite3 *db) {
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT, email TEXT, password TEXT,"
        "role TEXT, saldo INTEGER);"

        "CREATE TABLE IF NOT EXISTS item ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "item_name TEXT, category TEXT, price INTEGER,"
        "stock INTEGER);"

        "CREATE TABLE IF NOT EXISTS cart ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "user_id INTEGER, item_id INTEGER, quantity INTEGER, "
        "FOREIGN KEY(user_id) REFERENCES users(id),"
        "FOREIGN KEY(item_id) REFERENCES item(id));"

        "CREATE TABLE IF NOT EXISTS transaction ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "user_id INTEGER, item_id INTEGER, quantity INTEGER, total_price INTEGER,"
        "status TEXT"
        "FOREIGN KEY(user_id) REFERENCES users(id),"
        "FOREIGN KEY(item_id) REFERENCES item(id));";

        "CREATE TABLE IF NOT EXISTS shipping ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "from_city_id INTEGER, to_city_id INTEGER, cost INTEGER"
        "FOREIGN KEY(from_city_id) REFERENCES city(id)"
        "FOREIGN KEY(to_city_id) REFERENCES city(id));";

        "CREATE TABLE IF NOT EXISTS city ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "parent_id INTEGER,"
        "city_name STRING,"
        "FOREIGN KEY(from_city_id) REFERENCES city(id)"
        "FOREIGN KEY(to_city_id) REFERENCES city(id));";

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Database initialized.\n");
    }
}
