#ifndef ORDERS_H
#define ORDERS_H

typedef struct {
    float pizza_id;
    float order_id;
    char pizza_name_id[30];
    float quantity;
    char order_date[15];
    char order_time[10];
    float unit_price;
    float total_price;
    char pizza_size[5]; 
    char pizza_category[20];
    char pizza_ingredients[100]; 
    char pizza_name[50];
}order;

void structcsv(const char *filename, order **orders, int *size);

#endif