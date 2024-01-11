Please use the latest code (order_sys3. c) for the fixed version of the code. 

This is a program that mimics an ordering system. As you run the program, you'll see 3 choices: 
1. order  // use this option if you want to order
2. admin  // use this if you want to use admin functions such as add Products, remove Products, reset the list
3. exit   // select this if u want to exit

the username/password is both ->  "admin"
please be mindful to input correct info as the login ui only allows 3 attempts per run
it also have a character input limit of 8 characters, more than that it will over flow the buffer and will cause an error

when you login to the admin section this would appear:
1. list products  // it will list all the available products
2. add Products   // will allow you to add Products to the system, please don't forget to select (#5) to save your list, otherwise it won't be saved. 
3. remove Products // will allow you to remove Products to the system, please don't forget to select (#5) to save your list, otherwise it won't be saved. 
4. reset list   // will delete all the products in the list with one click
5. save/exit  // select this to save your list

note:
1. In the add products function, the product name should not contain [spaces]
2. The stock should not exceed 1000, otherwise it will be automatically set to 1000
3. The list can only hold 100 products
4. Don't forget to save/exit to save the list.

now, on the order section, to order please use the index of the product and input the quantity, please refer to the stocks to know if it is available 
each successful order, automatically reflects on the stocks
after selecting which to order, you'll be transported to the receipt section 
you'll see the grand total and it will ask you to pay, please input the amount that you'll pay, once done a file containing the receipt will be created

note:
if you input insufficient amount, the order will be automatically terminated as well as the program, stock won't be deducted


problem:
	-> whenever there's already an existing file receipt, the previous doesn't get overwritten by the new receipt 
