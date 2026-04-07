import glitter


def main():
    try:
        connection = glitter.establish_connection()
    except Exception as e:
        print(f"Failed to connect to server: {e}")
        return

    print("Login to your Glitter account:")
    username = input("Username: ")
    password = input("Password: ")
    user_data = glitter.authenticate_user(username, password, connection)

    if not user_data:
        print("Authentication failed.")
        connection.close()
        return

    print(f"\nWelcome {user_data['screen_name']} (User ID: {user_data['id']})")
    
    while True:
        print("AVAILABLE OPTIONS:")
        print("[0]  - Quit")
        print("[1]  - Private Search")
        print("[2]  - Extract Email")
        print("[3]  - Full Info(except email and password and username)")
        print("[4]  - Spam Likes")
        print("[5]  - Invalid Dated Post")
        print("[6]  - Historical Post")
        print("[7]  - Future Post")
        print("[8]  - Unexisting colored Post")
        print("[9]  - Test Weak PIN")
        print("[10] - Test Long Username")
        print("[11] - Anonimus Like")
        print("[12] - Short Password")
        print("[13] - Get Checksum")
        print("[14] - Same Screen Name")
        print("\nBug Bounty:")
        print("[15] - Login Challenge")
        print("[16] - Password Challenge")
        print("[17] - Cookie Challenge")
        print("[18] - Privacy Challenge")

        choice = input("\nEnter choice (0-18): ").strip()
        print()

        try:
            if choice == "0":
                print("Goodbye!")
                connection.close()
                break

            elif choice == "1":
                target = input("Enter screen name to check privacy: ")
                result = glitter.find_privet(connection, target)
                print(result)
                print()

            elif choice == "2":
                target = input("Enter screen name to extract email: ")
                result = glitter.harvest_email_address(connection, target)
                print(result)
                print()

            elif choice == "3":
                target = input("Enter screen name to extract all info(except email and password and username): ")
                result = glitter.find_every_info(connection, target)
                for key, value in result.items():
                    if key != 'mail':
                        print(f"{key}: {value}")
                print()

            elif choice == "4":
                num_of_likes = int(input("enter num of likes to add(from 1 to 20): "))
                while num_of_likes > 20 or num_of_likes < 1:
                    num_of_likes = int(input("try again: "))

                name = input("enter screen name to add likes to: ")

                result = glitter.execute_like(connection, name, user_data["id"], int(choice), num_of_likes)
                if result == 0:
                    print("Like spam sent.\n")
                else:
                    print("Like spam failed.\n")

            elif choice == "5":
                print("Creating post with zero date...")
                success = glitter.create_post(connection, user_data["id"], int(choice))
                if success:
                    print("Post created.\n")
                else:
                    print("Failed.\n")

            elif choice == "6":
                print("Creating post with old date...")
                success = glitter.create_post(connection, user_data["id"], int(choice))
                if success:
                    print("Post created.\n")
                else:
                    print("Failed.\n")

            elif choice == "7":
                print("Creating post with future date...")
                success = glitter.create_post(connection, user_data["id"], int(choice))
                if success:
                    print("Post created.\n")
                else:
                    print("Failed.\n")

            elif choice == "8":
                print("Creating post with invalid color...")
                success = glitter.create_post(connection, user_data["id"], int(choice))
                if success:
                    print("Post created.\n")
                else:
                    print("Failed.\n")

            elif choice == "9":
                result = glitter.weak_pin_or_pass(int(choice))
                if result:
                    print("Approved.\n")
                else:
                    print("Rejected.\n")

            elif choice == "10":
                length = input("Enter long username length: ")
                if length.isdigit():
                    approved = glitter.test_username(int(length))
                    if approved:
                        print("Approved.\n")
                    else:
                        print("Rejected.\n")
                else:
                    print("Invalid length input.\n")

            elif choice == "11":
                num_of_likes = int(input("enter num of likes to add(from 1 to 20): "))
                while num_of_likes > 20 or num_of_likes < 1:
                    num_of_likes = int(input("try again: "))

                name = input("enter screen name to add likes to: ")

                result = glitter.execute_like(connection, name, user_data["id"], int(choice), num_of_likes)
                if result == 0:
                    print("Like spam sent.\n")
                else:
                    print("Like spam failed with empty name.\n")

            elif choice == "12":
                result = glitter.weak_pin_or_pass(int(choice))
                if result:
                    print("Approved.\n")
                else:
                    print("Rejected.\n")
            
            elif choice == "13":
                name = input("Enter user name to get checksum: ")
                checksum = glitter.get_checksum(name)
                if checksum is not None:
                    print(f"Checksum: {checksum}\n")
                else:
                    print("Checksum not found.\n")

            elif choice == "14":
                name = input("Enter screen name to test double registration: ")
                success = glitter.same_name(name)
                if success:
                    print("Both registrations approved.\n")
                else:
                    print("At least one failed.\n")

            elif choice == "15":
                name = input("Enter user name to connect to: ")
                success = glitter.login_challenge(name)
                if success:
                    print("Connected successfuly.\n")
                else:
                    print("Conection failed.\n")

            elif choice == "16":
                s_name = input("Enter screen name to steal password: ")
                user_name = input("Enter user name to steal password: ")
                info = glitter.find_every_info(connection, s_name)
                password = glitter.password_challenge(user_name, info['id'])
                if password:
                    print("the password: ",password, "\n")
                else:
                    print("Stealing failed.\n")

            elif choice == "17":
                name = user_data['user_name']
                cookie = glitter.cookie_challenge(name)
                if cookie:
                    print("Cookie to this account: ",cookie,"\n")
                else:
                    print("Cookie calc failed.\n")

            elif choice == "18":
                name = input("Enter screen name to see search history: ")
                info = glitter.find_every_info(connection, name)
                history = glitter.privacy_challenge(connection, info['id'])
                if history:
                    print("his search history")
                    for name in history:
                        print(name)
                else:
                    print("Conection failed.\n")


            else:
                print("Invalid option. Try again.\n")

        except Exception as e:
            print(f"Error: {e}\n")


if __name__ == "__main__":
    main()