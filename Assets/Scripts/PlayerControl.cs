﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// Pull Test

public class PlayerControl : MonoBehaviour
{
    public float jumpPower;
    bool isJump;
    Rigidbody2D rigid;

    public float maxSpeed;


    void Awake()    // initiating
    {
        rigid = GetComponent<Rigidbody2D>();
    }

    void Update()
    {
        //Stop Speed
        if (Input.GetButtonUp("Horizontal"))
        {
            rigid.velocity = new Vector2(rigid.velocity.normalized.x * 0.5f, rigid.velocity.y);
        }
        // jump 구현
        if (Input.GetButtonDown("Jump") && !isJump)
        {
            isJump = true;
            rigid.AddForce(Vector2.up * jumpPower, ForceMode2D.Impulse);
        }

    }
    void FixedUpdate()
    {
        // 좌, 우 이동
        float h = Input.GetAxisRaw("Horizontal");
        rigid.AddForce(Vector2.right * h * 0.2f, ForceMode2D.Impulse);

        
        //Max Speed
        if (rigid.velocity.x > maxSpeed)
            rigid.velocity = new Vector2(maxSpeed, rigid.velocity.y);
        if (rigid.velocity.x < maxSpeed * (-1))
            rigid.velocity = new Vector2(maxSpeed * (-1), rigid.velocity.y);
        
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        Debug.Log("Collision Entered : " + collision.gameObject.name);
        isJump = false;
    }
}
