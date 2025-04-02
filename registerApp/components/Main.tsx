import { KeyboardAvoidingView, StyleSheet, Text, TextInput, View } from 'react-native'
import React, { useState } from 'react'
import MyButton from './MyButton'
import { useNavigation } from '@react-navigation/native'

const Main = () => {
    const navigation = useNavigation()

    const [login, setLogin] = useState("");
    const [password, setPassword] = useState("");

    const fetchUsers = () => {
        fetch("http://192.168.119.113:3000/register", {
            method: "POST",
            body: JSON.stringify({hejka: "skibidi"}),
            headers: {
                "Content-Type": "application/json"
            }
        })
    }

    return (
        <>
            <KeyboardAvoidingView style={styles.container}>
                <TextInput onChangeText={text => setLogin(text)} style={{ borderBottomWidth: 2, width: "50%", borderColor: "cornflowerblue" }}></TextInput>
                <TextInput onChangeText={text => setPassword(text)} style={{ borderBottomWidth: 2, width: "50%", borderColor: "cornflowerblue" }}></TextInput>
                <MyButton color='cornflowerblue' text='Skibidi' action={() => { fetchUsers() }} />
            </KeyboardAvoidingView>
        </>
    )
}

export default Main

const styles = StyleSheet.create({
    header: {
        flex: 1
    },
    container: {
        flex: 1,
        justifyContent: "center",
        alignItems: "center",
        gap: 15
    },
    footer: {
        flex: 1
    }
})