import { StyleSheet, Text, TouchableOpacity, View } from 'react-native'
import React from 'react'

interface MyButtonProps {
    color: string,
    text: string,
    action: () => void;
}

const MyButton = ({color, text, action}: MyButtonProps) => {
  return (
    <TouchableOpacity style={[styles.button, {backgroundColor: color}]} onPress={action}>
        <Text>
            {text}
        </Text>
    </TouchableOpacity>
  )
}

export default MyButton

const styles = StyleSheet.create({
    button: {
        display: "flex",
        alignItems: "center",
        padding: 10,
        borderRadius: 5,
        color: "white"
    }
})